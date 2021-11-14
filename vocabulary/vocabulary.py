#Vocabulary

import random

filebox = 'allfile.txt'

#Check if the word is exist
def CheckWordExist(lstname, inputword):
    for num in range(0, len(lstname)):
        if lstname[num] == inputword:
            return True
          
    return False

#Delete all contents in file
def CleanFile(fname):   
    with open(fname, 'w') as f:   
        f.truncate()

#Pack all contents in lines into a list
def ScanFile(fname, lstname):
    with open(fname) as f:
        for line in f:
            lstname.append(line.strip())
            
    return lstname

#Renew the file
def RenewFile(fname, lstname):
    with open(fname, 'w') as f:       
        for lst in lstname:
            f.write(lst + '\n')

#Pack all contents in words into a list
def ScanWord(fname, lstname, splitchar=' '):
    with open(fname, 'r') as f:
        for line in f:                          
            item = [i for i in line.split(splitchar)]
            lstname.append(item)
            
    return lstname
    
def ChangeFile(fbox, fname, optnumlst, allfilelst):  
    print('\n*Choose the number of files to open it\n')

    with open(fbox, 'r') as f:
        print('\n' + f.read() + '\n')

    while True:
        choose = int(input())
    
        if choose in optnumlst:                  
            print('\n*File import successfully!\n')
          
            break
        
        else:
            print('\n*Illegal inputs\n*Please input again!')
    
    fname = allfilelst[choose - 1][1]

    if fname[-1] == '\n':
        fname = fname[:-1]
    
    return fname
    
#Main program
allfile = []    #append each contents

ScanWord(filebox, allfile)

optnum = []    #append the amount of files

for i in range(len(allfile)):
    optnum.append(i + 1)

print('\n*Choose the number of files to open it\n')

with open(filebox, 'r') as f:
    print('\n' + f.read() + '\n')

while True:
    choose = int(input())
    
    if choose in optnum:                  
        print('\n*File import successfully!\n')
        
        break
        
    else:
        print('\n*Illegal inputs\n*Please input again!')
    
filename = allfile[choose - 1][1]

if filename[-1] == '\n':
    filename = filename[:-1]

save = []

while True:  
    words = []
    
    ScanFile(filename, words)
  
    print('\n*Input a number of the options\n'
    +' (1)Add new words\n'    
    +' (2)Remove words\n'    
    +' (3)Inspect the file\n'    
    +' (4)Clean file\n'    
    +' (5)Save contents\n'    
    +' (6)Return to lated archive\n'    
    +' (7)Vocabulary test\n'    
    +' (8)Change file\n'    
    +' (9)End the program\n')   

    option = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    options = int(input())

    if options in option:      
        if options == 1:           
            print('\n*Input a new word to add in this file(word/part of speech/meaning)\n*Input \"END\" to stop adding the word '
                  + '\n  and back to the options\n')
        
            while True:                   
                word_a = str(input())
      
                if word_a == 'END':                   
                    CleanFile(filename)
                    RenewFile(filename, words)
                            
                    print('\n*Add words successfully!\n')

                    break
        
                else:                    
                    Check = CheckWordExist(words, word_a)
                    
                    if Check == False:
                        words.append(word_a)
                        
                    else:
                        print('\n*The word has already exist!\n Please add other words\n')
      
        if options == 2:                     
            words2 = []
            
            ScanWord(filename, words2, '/')

            print('\n*Input a word you want to remove\n')

            word_r = str(input())           
            WordExist = False
            
            for i in range(len(words)):                         
                if word_r in words2[i][0]:                
                    WordExist = True
                    del words[i]
    
            if WordExist == False:              
                print('\n*This word is not exist!\n')
                
            else:                           
                CleanFile(filename)               
                RenewFile(filename, words)
                        
                print('\n*Remove the word successfully!\n')
  
        if options == 3:            
            with open(filename, 'r') as f:
                print('\n' + 30 * '=' + '\n\n' + f.read() + '\n\n' + 30 * '=' + '\n')
    
        if options == 4:         
            save = []
            
            ScanFile(filename, save)                            
            CleanFile(filename)
            
            print('\n*Clean file successfully!\n\n*The lated archive saved successfully!\n')
                
        if options == 5:
            save = []
            
            ScanFile(filename, save)
            
            print('\n*Save file successfully!')
                
        if options == 6:         
            CleanFile(filename)
            RenewFile(filename, save)        
                            
            print('\n*Return file successfully!\n')
    
        if options == 7:          
            words2 = []
            numlst = []
                    
            ScanWord(filename, words2, '/')
            
            for i in range(0, len(words2)):
                numlst.append(i)
                
            random.shuffle(numlst)
                
            print('\n' + 30 * '=' + '\n\n*Test Start!\n')
                
            life = 10
            count = 0
            count2 = 0
            
            while True:               
                if life == 0:
                    print('\n*Test Over!\n Please practice more!\n\n' + 30 * '=' + '\n')
                        
                    break
                
                elif count == len(numlst):                  
                    print('\n*Congratulations!\n You have answered all the questions!'
                          + '\n Test Over!\n\n' + 30 * '=' + '\n')
                        
                    break
                
                else:                  
                    rnum = numlst[count]
                    rword = words2[rnum][0]
                    lst = list(rword)
            
                    for i in range(1, len(lst) - 1):
                        if lst[i] != ' ':
                            lst[i] = '_'
                  
                    sub = str()
                
                    for i in range(0, len(lst)):
                        sub += str(lst[i])
                
                    print(str(count+1) + '. ' + sub + ' ' + words2[rnum][1] + ' ' + words2[rnum][2] + '\n')
                
                    ans = str(input())
                
                    if ans == rword:                           
                        count += 1
                        count2 += 1

                        print('\n*Correct!    Score:' + str(count2) + '\n\n' + 30 * '–' + '\n')

                    else:                       
                        life -= 1
                        count += 1

                        print('\n*Wrong answer!\n\n Correct answer:' + rword + '\n Life:' + str(life)
                              + '    Score:' + str(count2) + '\n\n' + 30 * '–' + '\n')
                                   
        if options == 8:                                           
            filename = ChangeFile(filebox, filename, optnum, allfile)

        if options == 9:
            break
    
    else:
        print('\n*Illegal inputs\n*Please input again!\n')

print('\n*Finish successfully!')
