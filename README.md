# FCP
FCP(Functinal communication protocol),TCP����ĳ���֮������ӣ���FCP������ǹ���(����)��
FCP�Է������Ļ���Ϊ���ģ���������̡���ƽ̨����״���硣

FCP aim to create a convenient way to transport data between devices.

## principle
1. AloneNode �����ڵ�
![AloneNode](doc/AloneNode.jpg)
2. PairNode ���ӽڵ�
![PairNode](doc/PairNode.jpg)

ÿ���ڵ㶼���Զ���������ת�������յ�����Ϣ�����ÿһ���ڵ㣨����Master)����һ�����ڵ㣨gateway�������ɸ��ӽڵ㣨child����
AloneNode ������һ�����������ͨѶ���硣��PairNode��Ҫʵ��Tx�����Ӳ��������ڲ�ͬ���̼�������硣

## ·��ϵͳ
������ڵ��������ʱ��ÿһ���ڵ��·����Ψһ�ġ��ڵ�����������������������ʽ��  
����Ҫ���ʽڵ�ʱ��������һ��URI��URI���Է���һ�������ڵ㣬Ҳ��ָ��������ĳЩ�ڵ㡣  

1. node_name :: [a-z]\\w*:\\d+(\\|\\d+)*
2. uri_name  :: [a-z]\\w*(:\\d+(\\|\\d+)*)?(!\\d+(\\|\\d+)*)?
3. node_path :: (/node_name)+|/
4. uri_path  :: (/uri_name)+|/

URI��3���÷���
- �㲥��node_name
- ����\�ಥ: node_name:num1|num2
- �ų��� node_name!num1|num2

