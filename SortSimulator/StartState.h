#ifndef STARTSTATE_H_INCLUDED
#define STARTSTATE_H_INCLUDED

#include <memory>
#include <deque>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include "Game.h"
#include "State.h"
#include "ClassObject.h"

class StartSort: public eng::State
{
    std::shared_ptr<Context> sptr_Context;
    std::deque<obj::Block> deq_BlkArr;
    sf::Text txt_SortName;
    sf::Text txt_ResetBtn;
    sf::Text txt_StartBtn;
    sf::Text txt_ReturnBtn;
    int  int_BtnIdx;
    int  int_CheckBlkIdx;
    int  int_SortIdx;
    int  int_MaxElemIdx;
    int  int_MinElemIdx;
    bool bl_IsResetSelected;
    bool bl_IsResetPressed;
    bool bl_IsStartSelected;
    bool bl_IsStartPressed;
    bool bl_IsReturnSelected;
    bool bl_IsReturnPressed;
    bool bl_Sorted;
    bool bl_IsSorting;
    bool bl_IsChecking;
    bool bl_HaveSwitch;

public:
    StartSort(std::shared_ptr<Context>& sptr_Context)
    {
        this->sptr_Context = sptr_Context;
        bl_IsResetPressed = false;
        bl_IsResetSelected = true;
        bl_IsReturnPressed = false;
        bl_IsReturnSelected = false;
        bl_IsStartPressed = false;
        bl_IsStartSelected = false;
        bl_Sorted = true;
        bl_IsSorting = false;
        bl_IsChecking = false;
        int_BtnIdx = int_SortIdx = 0;
        int_CheckBlkIdx = int_BlkCount - 1;

        for(int i = 0; i < int_BlkCount; i++)
        {
            obj::Block blk_Elem;

            deq_BlkArr.push_back(blk_Elem);
        }
    }
    ~StartSort(){}

    void fn_Return();
    void SwitchBtn()
    {
        switch(int_BtnIdx)
        {
            case 0:
                bl_IsResetSelected = true;
                bl_IsReturnSelected = bl_IsStartSelected = false;

                break;

            case 1:
                bl_IsStartSelected = true;
                bl_IsResetSelected = bl_IsReturnSelected = false;

                break;

            case 2:
                bl_IsReturnSelected = true;
                bl_IsResetSelected = bl_IsStartSelected = false;

                break;
        }
    }
    void Init() override
    {
        fn::PresetBlk(deq_BlkArr, int_BlkCount);

        // Sort Name
        txt_SortName.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));

        switch(int_SortAlgoIdx)
        {
            case BUBBLE_SORT: txt_SortName.setString("Bubble Sort"); break;
            case INSERTION_SORT: txt_SortName.setString("Insertion Sort"); break;
            case SELECTION_SORT: txt_SortName.setString("Selection Sort"); break;
        }

        txt_SortName.setCharacterSize(36);
        txt_SortName.setPosition(0, 0);

        // Reset Button
        txt_ResetBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_ResetBtn.setString("Reset Blocks");
        txt_ResetBtn.setCharacterSize(24);
        txt_ResetBtn.setPosition(0, 50);

        // Start Button
        txt_StartBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_StartBtn.setString("Start Sorting");
        txt_StartBtn.setCharacterSize(24);
        txt_StartBtn.setPosition(0, 75);

        // Return Button
        txt_ReturnBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_ReturnBtn.setString("Return");
        txt_ReturnBtn.setCharacterSize(24);
        txt_ReturnBtn.setPosition(0, 100);
    }
    void ProcessInput() override
    {
        sf::Event event;    // Process events

        while(sptr_Context->uptr_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) sptr_Context->uptr_Window->close();   // Close window : exit
            else if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Up:
                        if((!bl_IsSorting && !bl_IsChecking) && int_BtnIdx > 0) int_BtnIdx--;
                        SwitchBtn();

                        break;

                    case sf::Keyboard::Down:
                        if((!bl_IsSorting && !bl_IsChecking) && int_BtnIdx < 2) int_BtnIdx++;
                        SwitchBtn();

                        break;

                    case sf::Keyboard::Enter:
                        switch(int_BtnIdx)
                        {
                            case 0:
                                bl_IsResetPressed = true;
                                txt_ResetBtn.setString("Reseting . . .");

                                break;

                            case 1:
                                if(!bl_Sorted)
                                {
                                    bl_IsStartPressed = true;
                                    txt_StartBtn.setString("Sorting . . .");
                                }

                                break;

                            case 2:
                                bl_IsReturnPressed = true;

                                break;
                        }

                        break;

                    default: break;
                }
            }
        }
    }
    void Update(sf::Time deltaTime) override
    {
        if(bl_IsResetSelected)
        {
            txt_ResetBtn.setFillColor(sf::Color::Yellow);
            txt_StartBtn.setFillColor(sf::Color::White);
            txt_ReturnBtn.setFillColor(sf::Color::White);
        }
        else if(bl_IsStartSelected)
        {
            txt_StartBtn.setFillColor(sf::Color::Yellow);
            txt_ResetBtn.setFillColor(sf::Color::White);
            txt_ReturnBtn.setFillColor(sf::Color::White);
        }
        else if(bl_IsReturnSelected)
        {
            txt_ReturnBtn.setFillColor(sf::Color::Yellow);
            txt_StartBtn.setFillColor(sf::Color::White);
            txt_ResetBtn.setFillColor(sf::Color::White);
        }

        if(bl_IsReturnPressed) fn_Return();
    }
    void Draw() override
    {
        if(bl_IsSorting)
        {
            switch(int_SortAlgoIdx)
            {
                case BUBBLE_SORT:
                    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);
                    deq_BlkArr[int_SortIdx + 1].fn_SetColor(sf::Color::Red);

                    if(deq_BlkArr[int_SortIdx].int_Idx > deq_BlkArr[int_SortIdx + 1].int_Idx)
                    {
                        obj::Block blk_TempRval = deq_BlkArr[int_SortIdx];

                        deq_BlkArr[int_SortIdx] = deq_BlkArr[int_SortIdx + 1];
                        deq_BlkArr[int_SortIdx + 1] = blk_TempRval;

                        deq_BlkArr[int_SortIdx].fn_SetXPos(int_SortIdx, int_BlkCount);
                        deq_BlkArr[int_SortIdx].fn_SetRctPos();

                        deq_BlkArr[int_SortIdx + 1].fn_SetXPos(int_SortIdx + 1, int_BlkCount);
                        deq_BlkArr[int_SortIdx + 1].fn_SetRctPos();
                    }

                    sptr_Context->uptr_Window->clear();
                    sptr_Context->uptr_Window->draw(txt_SortName);
                    sptr_Context->uptr_Window->draw(txt_ResetBtn);
                    sptr_Context->uptr_Window->draw(txt_StartBtn);
                    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

                    bl_Sorted = true;

                    for(int i = 0; i < int_BlkCount; i++)
                    {
                        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);

                        if(i < int_CheckBlkIdx && deq_BlkArr[i].int_Idx > deq_BlkArr[i + 1].int_Idx) bl_Sorted = false;
                        if(i == int_CheckBlkIdx && deq_BlkArr[int_CheckBlkIdx].int_Idx == int_CheckBlkIdx) int_CheckBlkIdx--;
                    }

                    sptr_Context->uptr_Window->display();

                    deq_BlkArr[int_SortIdx].fn_SetColor();
                    deq_BlkArr[int_SortIdx + 1].fn_SetColor();

                    if(++int_SortIdx >= int_CheckBlkIdx) int_SortIdx = 0;

                    break;

                case INSERTION_SORT:
                    bl_HaveSwitch = false;

                    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

                    if(deq_BlkArr[int_SortIdx].int_Idx < deq_BlkArr[int_SortIdx - 1].int_Idx)
                    {
                        bl_HaveSwitch = true;

                        obj::Block blk_TempRval = deq_BlkArr[int_SortIdx];

                        deq_BlkArr[int_SortIdx] = deq_BlkArr[int_SortIdx - 1];
                        deq_BlkArr[int_SortIdx - 1] = blk_TempRval;

                        deq_BlkArr[int_SortIdx].fn_SetXPos(int_SortIdx, int_BlkCount);
                        deq_BlkArr[int_SortIdx].fn_SetRctPos();

                        deq_BlkArr[int_SortIdx - 1].fn_SetXPos(int_SortIdx - 1, int_BlkCount);
                        deq_BlkArr[int_SortIdx - 1].fn_SetRctPos();
                    }

                    sptr_Context->uptr_Window->clear();
                    sptr_Context->uptr_Window->draw(txt_SortName);
                    sptr_Context->uptr_Window->draw(txt_ResetBtn);
                    sptr_Context->uptr_Window->draw(txt_StartBtn);
                    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

                    for(int i = 0; i < int_BlkCount; i++)
                    {
                        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
                    }

                    sptr_Context->uptr_Window->display();

                    deq_BlkArr[int_SortIdx].fn_SetColor();

                    if(int_SortIdx == 1) deq_BlkArr[0].fn_SetColor();
                    if(--int_SortIdx == 0 || !bl_HaveSwitch) int_SortIdx = ++int_CheckBlkIdx;

                    bl_Sorted = (int_CheckBlkIdx == int_BlkCount);

                    break;

                case SELECTION_SORT:
                    if(deq_BlkArr[int_SortIdx].int_Idx < deq_BlkArr[int_MinElemIdx].int_Idx)
                    {
                        deq_BlkArr[int_MinElemIdx].fn_SetColor();

                        int_MinElemIdx = int_SortIdx;
                    }

                    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

                    sptr_Context->uptr_Window->clear();
                    sptr_Context->uptr_Window->draw(txt_SortName);
                    sptr_Context->uptr_Window->draw(txt_ResetBtn);
                    sptr_Context->uptr_Window->draw(txt_StartBtn);
                    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

                    bl_Sorted = true;

                    for(int i = 0; i < int_BlkCount; i++)
                    {
                        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);

                        if(i < int_BlkCount - 1 && deq_BlkArr[i].int_Idx > deq_BlkArr[i + 1].int_Idx) bl_Sorted = false;
                    }

                    sptr_Context->uptr_Window->display();

                    if(int_SortIdx != int_MinElemIdx)
                    {
                        deq_BlkArr[int_SortIdx].fn_SetColor();
                        deq_BlkArr[int_MinElemIdx].fn_SetColor(sf::Color::Red);
                    }
                    else deq_BlkArr[int_SortIdx].fn_SetColor();

                    if(++int_SortIdx == int_BlkCount)
                    {
                        if(int_CheckBlkIdx != int_MinElemIdx)
                        {
                            obj::Block blk_TempRval = deq_BlkArr[int_CheckBlkIdx];

                            deq_BlkArr[int_CheckBlkIdx] = deq_BlkArr[int_MinElemIdx];
                            deq_BlkArr[int_MinElemIdx] = blk_TempRval;

                            deq_BlkArr[int_CheckBlkIdx].fn_SetXPos(int_CheckBlkIdx, int_BlkCount);
                            deq_BlkArr[int_CheckBlkIdx].fn_SetRctPos();
                            deq_BlkArr[int_CheckBlkIdx].fn_SetColor();

                            deq_BlkArr[int_MinElemIdx].fn_SetXPos(int_MinElemIdx, int_BlkCount);
                            deq_BlkArr[int_MinElemIdx].fn_SetRctPos();
                        }

                        deq_BlkArr[int_MinElemIdx].fn_SetColor();

                        int_SortIdx = int_MinElemIdx = ++int_CheckBlkIdx;
                    }

                    break;

                default: break;
            }

            if(bl_Sorted)
            {
                txt_StartBtn.setString("Checking");

                bl_IsSorting = false;
                bl_IsChecking = true;
                int_SortIdx = 0;
            }
        }
        else if(bl_IsChecking)
        {
            deq_BlkArr[int_SortIdx++].fn_SetColor(sf::Color::Green);

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(int_SortIdx == int_BlkCount)
            {
                sptr_Context->uptr_Window->clear();
                sptr_Context->uptr_Window->draw(txt_SortName);
                sptr_Context->uptr_Window->draw(txt_ResetBtn);
                sptr_Context->uptr_Window->draw(txt_StartBtn);
                sptr_Context->uptr_Window->draw(txt_ReturnBtn);

                for(int i = 0; i < int_BlkCount; i++)
                {
                    deq_BlkArr[i].fn_SetColor();

                    sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
                }

                sptr_Context->uptr_Window->display();
                txt_StartBtn.setString("Start Sorting");

                bl_IsChecking = false;
            }
        }
        else
        {
            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(bl_IsResetPressed)
            {
                fn::RandomBlk(deq_BlkArr, int_BlkCount);

                txt_ResetBtn.setString("Reset Blocks");

                bl_IsResetPressed = false;
                bl_Sorted = false;
            }
            else if(bl_IsStartPressed && !bl_Sorted)
            {
                bl_IsStartPressed = false;
                bl_IsSorting = true;

                switch(int_SortAlgoIdx)
                {
                    case BUBBLE_SORT:
                        int_SortIdx = 0;
                        int_CheckBlkIdx = int_BlkCount - 1;

                        break;

                    case INSERTION_SORT:
                        int_SortIdx = 1;
                        int_CheckBlkIdx = 1;

                        break;

                    case SELECTION_SORT:
                        int_MinElemIdx = 0;
                        int_SortIdx = 0;
                        int_CheckBlkIdx = 0;

                        break;
                }
            }
        }
    }
};

#endif // STARTSTATE_H_INCLUDED
