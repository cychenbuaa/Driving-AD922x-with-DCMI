# Driving-AD922x-with-DCMI
Driving Extern High-speed ADC with STM32F4 DCMI
## 项目介绍
对于一般的 MCU 来说，通常难以驱动外部的中高速（10MSPS~50MSPS）ADC，对于这类并行输出的 ADC，可以采用 FPGA 驱动等方案。但如果可以使用 MCU 直接驱动 ADC，并可以同时完成项目中其他需求，就可以达到降低系统成本、复杂度，缩短开发周期的目标。

本项目使用具有 DCMI 接口的 STM32F407（关于还有哪些 STM32 系列芯片具有该接口，请[点击此处查看](http://www.st.com/content/ccc/resource/technical/document/application_note/group0/c0/ef/15/38/d1/d6/49/88/DM00373474/files/DM00373474.pdf/jcr:content/translations/en.DM00373474.pdf)），驱动外部高速 ADC（up to 54MHz）。实验测试使用的是 ADI 的 AD922x 系列并行 ADC ([AD9220
](http://www.analog.com/media/en/technical-documentation/data-sheets/AD9221_9223_9220.pdf)-10MSPS, [AD9224](http://www.analog.com/media/en/technical-documentation/data-sheets/AD9224.pdf)-40MSPS,该系列其他型号请参考 ADI 官网)

## 硬件
见

## 软件
使用 ST 库函数 V1.8.0 版本编程，如需参考，可自行建立基于库函数的项目工程
