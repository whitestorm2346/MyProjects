import os
import re
from flask import Flask, request, abort
from linebot import (LineBotApi, WebhookHandler)
from linebot.exceptions import (InvalidSignatureError)
from linebot.models import *
from firebase import *
from database import *

app = Flask(__name__)
line_bot_api = LineBotApi(channelAccessToken)
handler = WebhookHandler(channelSecret)
isfirststart = True

@app.route("/callback", methods=['POST'])
def callback():
    signature = request.headers['X-Line-Signature']
    body = request.get_data(as_text=True)

    app.logger.info("Request body: " + body)

    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        abort(400)

    return 'OK'

@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    global isfirststart

    msg = event.message.text
    print('Message received')
    each = [i for i in msg.split()]
    reply_msg = ''
    iscorrectcmd = False
    is_in_group = True
    is_in_room = True
    doc_id = ''

    try:
        group_id = event.source.group_id
    except Exception:
        is_in_group = False

    try:
        room_id = event.source.room_id
    except Exception:
        is_in_room = False

    if is_in_group:
        doc_id = event.source.group_id
    elif is_in_room:
        doc_id = event.source.room_id
    else:
        doc_id = event.source.user_id

    if isfirststart:
        isfirststart = False

        try:
            line_bot_api.push_message(doc_id, TextSendMessage(text=start_msg))
        except Exception:
            print('No more usage for push message.')

    doc_dict = firestore_client.collection('群組管理').document('設計格式').get().to_dict()
    doc_list = doc_dict['doc_id']

    if doc_id not in doc_list:
        firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').set({})
        firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('簡稱').set({})
        firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document('設計格式').set({})
        doc_list.append(doc_id)
        firestore_client.collection('群組管理').document('設計格式').update({'doc_id': doc_list})

    if re.match('/簡稱', each[0]) and len(each) == 1:
        iscorrectcmd = True
        reply_msg = GetAbbreviation(doc_id)
    elif re.match('/新增', each[0]) and len(each) == 3:
        if each[1] != '' and each[2] != '':
            iscorrectcmd = True
            abbrev = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('簡稱').get().to_dict()
            key_list = abbrev.keys()

            if each[1] in key_list:
                reply_msg = each[1] + '已經存在嘍~'
            else:
                firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('簡稱').update({each[1]: each[2]})

                reply_msg = '成功新增一個簡稱'
    elif re.match('/刪除', each[0]) and len(each) == 3:
        if re.match('簡稱', each[1]):
            iscorrectcmd = True
            abbrev = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('簡稱').get().to_dict()
            key_list = abbrev.keys()

            if each[2] in key_list:
                firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('簡稱').update({each[2]: firestore.DELETE_FIELD})

                reply_msg = '成功從簡稱列表中刪除\"' + each[2] + '\"'
            else:
                reply_msg = '\"' + each[2] + '\"並不存在簡稱列表中'
        elif re.match('活動', each[1]):
            iscorrectcmd = True
            event_code = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').get().to_dict()
            key_list = event_code.keys()

            if each[2] in key_list:
                code = event_code[each[2]]
                event_info = firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).get().to_dict()
                profile = line_bot_api.get_profile(event.source.user_id)

                if profile.display_name == event_info['發起人']:
                    event_name = event_info['活動名稱']

                    firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').update({each[2]: firestore.DELETE_FIELD})
                    firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).delete()

                    reply_msg = '成功從活動列表中刪除\"' + event_name + '\"'
                else:
                    reply_msg = '只有活動發起人有權限刪除活動'
            else:
                reply_msg = '找不到對應的活動，請確認後重新輸入指令'
    elif re.match('/預約', each[0]) and (len(each) == 3 or len(each) == 4):
        DateTime = SplitDateTime(each[2])

        if len(DateTime) == 5 and CheckCorrectDateTime(DateTime):
            iscorrectcmd = True
            profile = line_bot_api.get_profile(event.source.user_id)

            if len(each) == 3:
                firestore_client.collection('群組管理').document(doc_id).collection('活動列表').add({
                    "剩餘空位": -1,
                    "參與人員": [],
                    "日期": DateTime[0] + '/' + DateTime[1] + '/' + DateTime[2],
                    "時間": DateTime[3] + ':' + DateTime[4],
                    "活動名稱": each[1],
                    "發起人": profile.display_name
                })
                reply_msg = CreateEvent(profile.display_name, each, DateTime)
            elif len(each) == 4:
                firestore_client.collection('群組管理').document(doc_id).collection('活動列表').add({
                    "剩餘空位": int(each[3]),
                    "參與人員": [],
                    "日期": DateTime[0] + '/' + DateTime[1] + '/' + DateTime[2],
                    "時間": DateTime[3] + ':' + DateTime[4],
                    "活動名稱": each[1],
                    "發起人": profile.display_name
                })
                reply_msg = CreateEvent(profile.display_name, each, DateTime)
        else:
            iscorrectcmd = True

            reply_msg = '日期與時間的格式有誤\n'\
                        '請修正後再次輸入指令\n\n'\
                        '格式：年(西元)/月/日/時(24hr)/分\n'\
                        '你的指令：' + each[2]
    elif re.match('/報名', each[0]) and (len(each) == 2 or len(each) == 3):
        iscorrectcmd = True
        event_code = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').get().to_dict()
        key_list = event_code.keys()

        if each[1] in key_list:
            code = event_code[each[1]]
            event_dict = firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).get().to_dict()
            profile = line_bot_api.get_profile(event.source.user_id)
            last_num = int(event_dict['剩餘空位'])
            need_num = 0
            iscorrectnum = True

            if len(each) == 2:
                need_num = 1
            elif len(each) == 3:
                need_num = int(each[2])

                if need_num < 1:
                    iscorrectnum = False
                    reply_msg = '報名人數應為大於或等於1的整數，請修正後再次輸入指令'

            if last_num != -1 and (last_num - need_num < 0 and iscorrectnum):
                reply_msg = '報名失敗，該活動的空位不足，下次報名請早~'
            elif iscorrectnum:
                already_sign_up = False

                for item in event_dict['參與人員']:
                    name_num = item.split()

                    if profile.display_name == name_num[0]:
                        already_sign_up = True

                        break

                if already_sign_up:
                    reply_msg = '您已經報名過\"' + event_dict['活動名稱'] + '\"嘍~\n'\
                                '若是要更動參與人數，請使用更動指令。'
                else:
                    if last_num != -1:
                        event_dict['剩餘空位'] = int(last_num - need_num)

                    event_dict['參與人員'].append(profile.display_name + ' ' + str(need_num))
                    firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).update(event_dict)

                    reply_msg = '成功報名參與\"' + event_dict['活動名稱'] + '\"，別忘了準時參與~'
        else:
            reply_msg = '找不到對應的活動，請確認後重新輸入指令'
    elif re.match('/取消', each[0]) and len(each) == 2:
        iscorrectcmd = True
        event_code = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').get().to_dict()
        key_list = event_code.keys()

        if each[1] in key_list:
            code = event_code[each[1]]
            event_dict = firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).get().to_dict()
            profile = line_bot_api.get_profile(event.source.user_id)
            already_sign_up = False

            for item in event_dict['參與人員']:
                name_num = item.split()

                if profile.display_name == name_num[0]:
                    already_sign_up = True

                    event_dict['參與人員'].pop(event_dict['參與人員'].index(item))

                    if event_dict['剩餘空位'] != -1:
                        event_dict['剩餘空位'] = int(event_dict['剩餘空位']) + int(name_num[1])

                    firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).update(event_dict)

                    reply_msg = '成功取消報名\"' + event_dict['活動名稱'] + '\"'

                    break

            if not already_sign_up:
                reply_msg = '您尚未報名參與\"' + event_dict['活動名稱'] + '\"'
        else:
            reply_msg = '找不到對應的活動，請確認後重新輸入指令'
    elif re.match('/活動', each[0]):
        iscorrectcmd = True
        event_doc = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號')
        event_code = event_doc.get().to_dict()
        key_list = event_code.keys()

        if each[1] in key_list:
            code = event_code[each[1]]
            event_dict = firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).get().to_dict()

            reply_msg = GetEventInfo(event_dict)
        else:
            reply_msg = '找不到對應的活動，請確認後重新輸入指令'
    elif re.match('/代號', each[0]) and len(each) == 1:
        iscorrectcmd = True
        code_list = GetEventList(firestore_client.collection('群組管理').document(doc_id).collection('活動列表'))

        RefreshEventList(code_list, doc_id)

        code_text = ''
        code_dict = {}

        if len(code_list) > 0:
            for item in code_list:
                idx = code_list.index(item)
                event_dict = firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(item).get().to_dict()
                code_dict[str(idx + 1)] = item
                code_text += str(idx + 1) + '-> ' + event_dict['活動名稱'] + ' ' \
                           + event_dict['日期'] + ' ' + event_dict['時間'] + '\n'

            code_text = code_text[:-1]

            firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').set(code_dict)

            reply_msg = code_text
        else:
            reply_msg = '目前沒有任何活動'
    elif re.match('/更動', each[0]) and len(each) == 3:
        iscorrectcmd = True
        event_code = firestore_client.collection('群組管理').document(doc_id).collection('RO副本管理').document('活動代號').get().to_dict()
        key_list = event_code.keys()

        if each[1] in key_list:
            code = event_code[each[1]]
            event_dict = firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).get().to_dict()
            profile = line_bot_api.get_profile(event.source.user_id)
            already_sign_up = False
            iscorrectnum = True
            last_num = int(event_dict['剩餘空位'])
            new_Num = int(each[2])

            if new_Num < 1:
                iscorrectnum = False
                reply_msg = '人數應為大於或等於1的整數，請修正後再次輸入指令'

            if iscorrectnum:
                for item in event_dict['參與人員']:
                    name_num = item.split()

                    if profile.display_name == name_num[0]:
                        already_sign_up = True
                        origin_num = int(name_num[1])

                        if (last_num - (new_Num - origin_num) < 0) and last_num != -1:
                            reply_msg = '更動失敗，該活動剩餘空位不足'

                            break

                        event_dict['參與人員'].pop(event_dict['參與人員'].index(item))
                        event_dict['參與人員'].append(name_num[0] + ' ' + str(new_Num))

                        if last_num != -1:
                            event_dict['剩餘空位'] = int(event_dict['剩餘空位']) - int(new_Num - origin_num)

                        firestore_client.collection('群組管理').document(doc_id).collection('活動列表').document(code).update(event_dict)

                        reply_msg = '成功更動於\"' + event_dict['活動名稱'] + '\"的參與人數'

                        break

            if not already_sign_up and not iscorrectnum:
                reply_msg = '您尚未報名參與\"' + event_dict['活動名稱'] + '\"'
        else:
            reply_msg = '找不到對應的活動，請確認後重新輸入指令'
    elif re.match('你好', each[0]) or re.match('安安', each[0]):
        iscorrectcmd = True
        profile = line_bot_api.get_profile(event.source.user_id)
        reply_msg = profile.display_name + ' ' + each[0]
    elif re.match('/自我介紹', each[0]) and len(each) == 1:
        iscorrectcmd = True
        reply_msg = self_intro
    elif re.match('/離開', each[0]) and len(each) == 1:
        iscorrectcmd = True

        if is_in_group:
            line_bot_api.reply_message(event.reply_token, TextSendMessage(text='有緣再見啦~'))
            line_bot_api.leave_group(event.source.group_id)
        elif is_in_room:
            line_bot_api.reply_message(event.reply_token, TextSendMessage(text='有緣再見啦~'))
            line_bot_api.leave_room(event.source.room_id)
        else:
            reply_msg = 'RObot並不存在群組或房間裡'
    elif re.match('/指令', msg):
        iscorrectcmd = True
        reply_msg = CmdMsg

    if (not iscorrectcmd) and msg[0] == '/':
            reply_msg = Wrong + CmdMsg

    if reply_msg != '':
        line_bot_api.reply_message(event.reply_token, TextSendMessage(text=reply_msg))

if __name__ == "__main__":
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port)
