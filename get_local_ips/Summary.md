Get Local IP Information by SIOCFIGCONF
===

###缘起

---
今天在coding的时候需要获得自己本机IP,本来以为是一件很简单的事情,用getsockname就可以搞定了呀~.但仔细想想之后,好像又不是那么回事.当我PC同时连上有线和无线的时候,有两个IP,如果我希望我拿到就是WIFI的那个IP,貌似就不是那么容易的事情了.于是继续google+baidu+man-page.最后决定用ioctl这个神器=.=

###收获
我主要参考的是这篇[文章](http://zhumeng8337797.blog.163.com/blog/static/1007689142012311082638/),很长..相当长...但是其实是把一样的内容重复了好几遍,我把链接放在这里只是因为我真的是看的它...


###拓展

---
1. 其实这三种类型: `sockaddr_in.sin_addr == long == unsigned char[4]`<br/>
*Ps:关于如何找到位置类型所在的头文件,然后查看其具体的定义,可以使用 `grep -R`,例如在这里,我们用 `grep -R 'sin_addr' /usr/include/` 找到这个变量在/usr/include/netinet/in.h中定义,然后就进入这个文件自己找吧:)*

2. 可以用这样的方式来查看IP地址: `printf("ip: %x 是: %3u.%3u.%3u.%3u",long, char[0], char[1], char[2], char[3]);`

3. 简单整理一下几个用于IP变量类型转换的函数: 

- inet_ntoa : long(网络字节序) -> char *
- inet_aton : char * -> long(网络字节序)

> inet_aton() converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary form (**in network byte order**) and stores it in the structure that inp points to. 

- inet_addr : char * -> long(网络字节序) **有255bug**

> The inet_addr() function converts the Internet  host  address cp from IPv4  numbers-and-dots notation into binary data **in network byte order**.

- inet_network : char * -> long(主机字节序) **有255bug**

> The inet_network() function converts cp, a string in IPv4  numbers-and-dots  notation, into a number **in host byte order** suitable for use as an Internet  network  address.

- 这里所谓的255bug是只当IP为255.255.255.255时,函数会返回0xffffffff,这本身没有错,也应该是全f,但是,在函数的定义和说明中,当输入非法的时候,返回值为-1,于是,问题就出来了.inet_aton函数没有这个bug是因为它把返回0认为出错,非0表示正确...对于这种做法..我只能说..太贱了 ->_->

> inet_addr(): If the input is invalid, INADDR_NONE (usually -1) is returned. Use of this function is problematic because -1 is a valid address (255.255.255.255).
> inet_aton() returns nonzero if the address is valid, zero if not.

- 当然还有很多其他类似的,具体参考inet_addr的man-page吧: `man inet_addr`
