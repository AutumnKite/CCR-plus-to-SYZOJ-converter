# 从 CCR Plus 到 SYZOJ 的数据配置格式转换器

[CCR Plus 项目地址](https://github.com/sxyzccr/CCR-Plus)

[SYZOJ 项目地址](https://github.com/syzoj/syzoj)

代码中引用了 [TinyXML 解析库](http://www.grinninglizard.com/tinyxml/)，感谢 TinyXML 的作者。

## 使用方法

在同目录下放置 CCR Plus 的数据配置文件 `.prb`。

在命令行中输入命令

```plain
g++ converter.cpp -o converter -std=c++11 -O2
```

直接运行生成的可执行文件 `converter.exe`（Windows） / `converter`（Linux）即可得到 SYZOJ 的数据配置文件 `data.yml`。

## 输出信息

若程序输出

```plain
Failed to load file ".prb".
```

则说明 `.prb` 文件不存在或 xml 语法有误。

若输出

```plain
No subtasks.
```

则说明不存在任何 subtask 或 `.prb` 文件中对 subtask 的描述有误。

```plain
No test cases.
```

则意味着存在 subtask 但所有 subtask 中都不存在测试点或测试点描述有误。

```plain
Cannot recognize the common part of the filename.
```

表示现在的测试数据文件名无法转换，具体参见注意事项中的第 3 条。

以上情况皆为一些无法正常转换的情况。

若程序输出

```plain
Success.
```

则说明转换成功。

文件中的 `.prb` 和 `data.yml` 即为一组转换成功的例子。

## 注意事项

1. 目前只支持传统题的配置。
2. 由于 CCR Plus 的 Special Judge 只需要可执行文件，而 SYZOJ 的 Special Judge 需要源代码，故无法自动配置。
3. **SYZOJ 的配置文件中，同组数据输入输出文件名的 `#` 是用同一字符串代替的，所以输入输出文件名的格式限制较大，可能存在无法转换的情况。**
