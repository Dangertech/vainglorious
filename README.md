# vainglorious
*A feature-rich "hacking" simulator for your terminal*

![](https://media0.giphy.com/media/fZe4mbL93LfxbNwtpE/giphy-downsized-medium.gif?cid=fbf3ecf85a15561cf8454003c35249ce78b69bd0c9de56e7&rid=giphy-downsized-medium.gif&ct=g)

Do you know [hackertyper.net](https://hackertyper.net)? The website that let's you look "cool", let's you look
like you're infiltrating the network, hacking the mainframe, like you just "got in"? Yeah, I know, it's for children.
But what if you had that website, with more features and customization options in your terminal? With custom themes,
setting your own code up as text to scroll through, customizing the scrolling, and much more?

Vainglorious aims to place itself in a line of awesome do-nothing-but-look-cool tools like [cmatrix](https://github.com/levithomason/cmatrix),
[neo](https://github.com/st3w/neo), [hollywood](https://github.com/dustinkirkland/hollywood), [dekryptize](https://github.com/mjosaarinen/dekryptize)
and more. It integrates fantastically into these stereotype low-res hacker montages where a guy in a black hoodie frantically smashes around on the 
keyboard, while the camera flings around all the time with some generic rap in the background.

## Features

Vainglorious has 14 distinct properties you can edit (pretty much every aspect I could come up with), all of which is explained by using `vain --help`.
However, there are some aspects I want to point out:

### Scrollfiles
You can give vainglorious a file to read text snippets from through `vain -f epic-python.scroll`. The file should be
divided into 'blocks' of text, separated by empty lines. The default scroll file is usually located at `/usr/share/vainglorious/default.scroll`
and contains 235 blocks (6453 lines) of C and C++ code already. If your computer is *really*, and I mean *really* slow,
you can limit until where the scrollfile is read by using `vain --until <line>`.

### Default themes
You can change the theme from the green one to 10 others with `vain --theme <theme-id/theme-name>`! These are all straight up stolen
from [neo's](https://github.com/st3w/neo) themes(with lots of open-source love). The themes (and the custom ones!) use an elaborate
system with weighted appearance rates and minimum and maximum appearance length for each color.

### Colorfiles
You can let vainglorious use your own theme! One line defines one color, it's **minimum and maximum appearance length** and it's appearance **rate**.
The first line is an exception, it only contains a color and sets the background.

Example:
```
#000000 % First line defines background color

%Color, minimum length, maximum length, probability
#38b27f, 3, 5, 5
#6df1d8, 3, 4, 3
92, 44, 109, 4, 6, 4 % Color can be given either in HEX or RGB format
#5da4a6, 4, 6, 4
#b8aec8, 2, 5, 3
#3c345c, 2, 3, 1
```

## Installation
Straightforward, as with pretty much every project with a makefile:

```
$ git clone https://github.com/Dangertech/vainglorious
$ cd vainglorious
$ make
# make install
```
