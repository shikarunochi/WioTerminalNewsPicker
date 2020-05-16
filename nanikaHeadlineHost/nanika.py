import random
import gc
import time
import YahooHeadline
import serial 

ser = serial.Serial("COM10", baudrate=115200 ,parity=serial.PARITY_NONE)

class nanika:
    
    def __init__(self):
        self.wordList = ["それな","そやな","しらんがな","まじか・・・","ぴえん","エモ散らかし","わかる","うける","はつみみ","あー、あれね","どゆこと？",
                "なるほどー","完全に理解","しってた","そっちかー","はじまったな","そっすね","それだ！","ええーっ！？","何だってー！",
                "株の買い時！","最の高では？","と、いうと？","神！","ふーん","わかるわかる","なんでや！","ワンチャン","ションボリ","もう限界では",
                "まだいける！","いわゆる神","高まっている","わかりみ","情報量が多い","何て？","もう見た","#拡散希望","なるはやで！"]

        random.seed(int(time.time()))

        #Yahooヘッドライン取得（XML）
        self.maxCategoty = YahooHeadline.getCategoryCount()
        self.nowCategory = 4
        self.titleTextList = YahooHeadline.getYahooHeadline(self.nowCategory)
        self.nowTitleIndex = 0

        self.nextNews()

        self.autoNewsCount = 0
        self.autoNews()

    def nextNews(self):
        self.autoNewsCount = 0
        lastNewsFlag = False
        if len(self.titleTextList) ==0 :
            return

        newsText = self.titleTextList[self.nowTitleIndex]
        position = 0
        sendText = ""
        newsTextLength = len(newsText)
        rowCount = 0
        while True:
            sendText = sendText + "  " + newsText[position:position+7] + "\n"
            if position >= newsTextLength:
                break
            rowCount = rowCount + 1
            if rowCount >= 3:
                break;
            position = position + 7
        ser.write(bytes(sendText + ":" + random.choice(self.wordList) + ":" + str(rowCount) +  ";", 'UTF-8'))
        print("send:" + newsText + ":" + str(rowCount))
        ser.flush()

        self.nowTitleIndex = self.nowTitleIndex + 1
        if self.nowTitleIndex >= len(self.titleTextList):
            self.nowTitleIndex = 0
            lastNewsFlag = True
        return lastNewsFlag

    def nextCategory(self):
        self.autoNewsCount = 0
        self.nowCategory = self.nowCategory + 1
        if self.nowCategory >= self.maxCategoty:
            self.nowCategory = 0
        self.titleTextList = YahooHeadline.getYahooHeadline(self.nowCategory)
        self.nowTitleIndex = 0
        self.nextNews()

    def autoNews(self):
        lastNewsFlag = False
        while True:
            time.sleep(1)
            self.autoNewsCount = self.autoNewsCount + 1
            if self.autoNewsCount > 5:
                if lastNewsFlag == True:
                    self.nextCategory()
                    lastNewsFlag = False
                else:
                    lastNewsFlag = self.nextNews()

mainObj = nanika()

                  