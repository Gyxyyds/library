## 小型图书馆信息管理系统

### 功能简介：

1. 本系统具有两种不同用户角色：管理员和普通读者，管理员只有一个，初始用户名为 manager，初始密码为：888888。首次使用时应提示管理员用户修改用户名或密码。读者用户不能自由注册，只能由管理员在系统中创建。读者用户的用户名固定为身份证号，密码默认为身份证号的后六位，读者用户登录后也需要提示其修改默认密码；
2. 管理员登录系统后，可以进行的操作：修改自己的用户名和密码、添加读者用户、删除读者用户、修改读者用户信息、查询读者用户信息（至少支持通过工号、姓名、手机号、身份证号等方式进行精确或模糊查询）、查询借阅和归还记录、增加图书信息、删除图书信息、修改图书信息、查询图书信息；
3. 读者用户登录后，可以进行的操作：修改自己的登录密码、查看自己的个人信息、查看自己的借阅和归还图书的记录、借书、还书；
4. 读者用户信息至少包括身份证号、密码、姓名、性别、手机号、住址等字段。图书信息包括 ISBN、图书名称、图书作者、出版社、数量、余量等字段。图书借还记录信息至少包括读者身份证号、ISBN、借出时间、归还时间、借出数量、备注；
5. 为了保障信息安全，所有密码等隐私敏感信息应该加密后存放，防止泄漏。

### 作者：

郭阳星

### 时间：

2023-9-4

