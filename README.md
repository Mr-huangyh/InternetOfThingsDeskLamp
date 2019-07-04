# InternetOfThingsDeskLamp
**使用ESP8266模块的Arduino板子，通过路由监听对台灯电源控制(物联网)项目**
## 使用材料(某宝均有售)
1. 一块有ESP8266的Arduino板子
2. 杜邦线*n
3. 继电器模块（5V低电平触发）
4. 一个报废3V/5V的学生台灯（或者是LED灯板，灯珠都可以）

## 项目过程

1. 先按照图片所示连接好所有的线

![Img](https://github.com/Mr-huangyh/InternetOfThingsDeskLamp/blob/master/1.jpg?raw=true "Img")

> 这里我用的是D4接口，当做触发接口，因为我这块板子，D4接口就刚好在3V,G的接口旁边，所以就使用了D4这个接口，如果想要改成其他接口，只需要把`digitalWrite(D4, LOW);`和`digitalWrite(D4, HIGH);`中的D4改成你接入的接口就好了。

2. 设置WIFI和密码

> 源码中的`const char* ssid = "CCCC";const char* password = "CCCC123456";`,其中`CCCC`就是WIFI的名称，`CCCC123456`就是WIFI密码。更换成自己的就可以了。

2. 刷入固件，下载这里的`HelloServer.ino`文件正常烤录就可以了。

## 可能遇到的问题(我也遇到的问题)

1. 提示未安装CH340G驱动(识别不到板子)

百度下载好CH340G驱动安装，或者找卖家客服也可以的，每个人的板子的usb转串口芯片不同，最好还是找卖家客服要，比较稳当。

2. 刷入不成功

这是一个什么状态呢，明明显示刷入成功了，但是实际上运行不起来，我的解决方案就是，把板子先刷干净，再刷入内容，用clear.ino这个文件就基本能刷干净，但是具体flash的型号不同，大小也不一样，然后把512改成自己flash的大小，最好也查清楚之后，清干净了，再刷进去，基本能解决百分之99的意外。
