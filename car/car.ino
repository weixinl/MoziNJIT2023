#include <IRremote.h>
const int irReceiverPin =7;  //定义红外接收模块的信号接收为D7引脚 
const int ledPin1 = 13;       //将D13引脚定义为双色LED绿灯的信号输出引脚
const int ledPin2 = 12;       //将D12引脚定义为双色LED红灯的信号输出引脚
IRrecv irrecv(irReceiverPin); //定义一个红外接收模块信号的变量
decode_results results;
void setup()
{
  pinMode(ledPin1,OUTPUT);   //定义LED信号输出引脚
  pinMode(ledPin2,OUTPUT);   //定义LED信号输出引脚
  Serial.begin(9600);     //定义波特率
  irrecv.enableIRIn();    //给红外接收模块进行使能 
}
void loop() 
{
  if (irrecv.decode(&results)) //当红外接收模块接收到信号时
  { 
    Serial.print("irCode: "); //打印出"irCode: " 
    Serial.print(results.value, HEX); //打印出当前信号16进制的值
    Serial.print(", bits: "); //打印出" , bits: " 
    Serial.println(results.bits); //打印出比特值
    irrecv.resume(); // 接收下一个信号
  } 
  delay(600); //延时600毫秒（按键消抖）
  if(results.value == 0xFFA25D)//如果接收到的信号为0xFFA25D
  {
    digitalWrite(ledPin1,HIGH);//点亮LED1
  }
  else if(results.value == 0xFFE21D)//如果接收到的信号为0xFFE21D
  {
    digitalWrite(ledPin2,HIGH);//点亮LED2
  }
  else
  {
    digitalWrite(ledPin1,LOW);//熄灭LED1
    digitalWrite(ledPin2,LOW);//熄灭LED2
  }
}