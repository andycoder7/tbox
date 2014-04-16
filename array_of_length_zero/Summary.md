[Arrays of Length Zero](http://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html)
===

###缘起

---
今天在和朋友聊天的时候突然料到了零长数组（arrays of length zero）或是叫可变数组，
或者叫变长数组（flexible array），或者叫柔性数组，anyway，反正就是那个长度为0的数组。
举个例子来说就是 `char contents[0]` 。作为一个对C不是很了解的人来说，很好奇这玩意是干嘛用的？
于是写了一些简单的测试程序，并用gdb啥的看了一下内存使用，还是似懂非懂，最后妥协了，
在万能的oschina中提出了我问题，我当时的题目是[长度为0的数组的size为什么不一定是0？](http://www.oschina.net/question/1470892_151368)。
（*Ps：我这里不好意思的说一下，由于当时我想复杂了，各种想不通，竟然忘了对齐的问题。。。真是弱爆了*）
虽然问题没有问到点上，但是还是有好心人给出了我要的答案：[C语言结构体里的成员数组和指针](http://coolshell.cn/articles/11377.html)。
如果对这个问题感兴趣的同学也可以参考一下陈皓大大的这篇文章，相信会有所收获的：）

###总结

---
柔性数组一般可以用来动态的扩展struct，用gcc上的[例子](http://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html)来说
	
	struct line {
		int length;
		char contents[0];
	};
	struct line *thisline = (struct line *)
		malloc (sizeof (struct line) + this_length);
	thisline->length = this_length;

相信代码已经能说明很多了吧，如果还是不理解的话，我再写一下这个struct的用法吧

	for (i = 0; i < (thisline->length - 1); i++) {
			thisline->contents[i] = 'a' + i%26;
	}
	thisline->contents[thisline->length - 1] = 0;
	//数组长10位，最后一位置为'\0'，所以应该只会输出9个字符
	puts(thisline->contents);

具体的test code可以在[边上的test.c](test.c)中看到。

###零碎

---
> - 对数组 `char c[10]` 来说，c和&c是一样的，都是c[0]的地址
> - 对于一个结构体中有short或者uint8_t的类型的变量时，有可能需要考虑对齐问题，
具体可参考陈皓大大的[深入理解C语言](http://coolshell.cn/articles/5761.html)一文
> - 我果然还是不会表述问题，不会写博客，第一次写，感脚好烂。。。希望对能对你有帮助

*Andy 2014-04-16*
