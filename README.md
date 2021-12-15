# robot_system
ロボットシステム学で利用したデバイスドライバ
***
# 実装内容  
講義で作成したデバイスドライバを使用し、  
echo 1 >> /dev/myled0  
上記のように入力するとLEDが点灯し  
echo 0 >> /dev/myled0  
と入力するとLEDが消灯する。  
***
# 必要なもの  
* Raspberry Pi 3+
* LED * 1  
* ブレットボード  
* 220Ω抵抗  
***
# 利用した回路  
以下の写真のように回路を作りました。  
<img src="https://github.com/ryosukehayashi3/robot_system/blob/main/S__112566278.jpg" width="320">  
LEDはアノードがGPIO25にGNDはさしやすいところで問題ありません。  
***
# ビルド方法  
`$ make`  
`$ sudo insmod myled.ko`  
`$ sudo chmod 666 /dev/myled0`  
***
# 実行結果  
`$ echo 1 >> /dev/myled0`  

`$ echo 0 >> /dev/myled0`  
