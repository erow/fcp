# FCP
Functinal communication protocol, aim to create a convenient way to transport data between devices.

## principle
1. subscribe
2. publish
3. address: /~:number
4. data type


FcpMessage
- direction :: 0:向子节点发送，1:向父节点发送,2：上下节点之间
- data  :: 传输内容
- type  :: 传输的类型