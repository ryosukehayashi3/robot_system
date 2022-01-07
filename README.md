# robot_system
ロボットシステム学で利用したデバイスドライバ
こちらは講義内で上田先生に作っていただいた[デバイスドライバ](https://github.com/ryuichiueda/robosys_device_drivers/blob/master/myled.c)
を改造したものです。
***
# 実装内容  
講義で作成したデバイスドライバを使用し、  
echo 1 >> /dev/myled0  
上記のように入力するとLED2つが点灯しブザーがなります。  
echo 0 >> /dev/myled0  
と入力するとLEDが消えブザーがも消音します。
***
# 必要なもの  
* Raspberry Pi 3+
* LED * 2  
* ブレットボード  
* 220Ω抵抗*3  
* ブザー  
***
# 利用した回路  
以下の写真のように回路を作りました。  
<img src="https://user-images.githubusercontent.com/94128516/146244268-42220ff1-2d94-42e7-85cd-d25c9455e6f1.jpg" width="320">  
LEDはアノードがGPIO25にGNDはさしやすいところで問題ありません。  
***
# ビルド方法  
`$ git clone git@github.com:ryosukehayashi3/robot_system.git`  
`$ cd robot_system/myled`  
`$ make`  
`$ sudo insmod myled.ko`  
`$ sudo chmod 666 /dev/myled0`  
***
# 実行結果  
`$ echo 1 >> /dev/myled0`  
<img src="https://user-images.githubusercontent.com/94128516/148500777-995b65ac-62b0-4d05-90bd-1ef85af45c53.jpg" width="320">  
`$ echo 0 >> /dev/myled0`  
<img src="https://user-images.githubusercontent.com/94128516/146244268-42220ff1-2d94-42e7-85cd-d25c9455e6f1.jpg" width="320">  
***
# 動画  
YouTubeに投稿した動画がこちらになります。  
<https://youtu.be/ktQ407pb7zc>
***
# ライセンス  
[GNU General Public License v3.0](https://github.com/ryosukehayashi3/robot_system/blob/main/LICENSE)
