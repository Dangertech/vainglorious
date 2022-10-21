# vainglorious
*A feature-rich "hacking" simulator for your terminal*

![](https://media1.giphy.com/media/fZe4mbL93LfxbNwtpE/giphy-downsized-medium.gif?cid=fbf3ecf840c76d7334bb3cda319afed162e22aea9ed3b1b5&rid=giphy-downsized-medium.gif&ct=g)

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

### Buttons
There are two special key combinations:
- `CTRL-D` to exit vainglorious
- `CTRL-L` to refresh the screen and clear eventual artifacts

## Installation
Only GNU/Linux systems are supported, but you should be able to compile on other operating systems with some changes too.

### Requirements
- g++
- ncurses development libraries (often called `ncurses-dev` or `ncurses-devel` in binary package managers)
- watch out, you might need to add `EXTRAS="-ltinfo"` to the `make` commands on some distributions.

The actual installation
is traightforward, as with pretty much every project with a makefile:

```
$ git clone https://github.com/Dangertech/vainglorious
$ cd vainglorious
$ make
# make install
```

The resulting executable is called `vain` and should be accessible
system-wide.

### Troubleshooting

#### Makefile fails at linking stage with "undefined reference to..."
Your package manager does weird stuff and enjoys the pain
and suffering of its users. The ncurses libraries are not fully
included in the default flags given to the linking command.
I only experience this issue on Gentoo, and it is fixable by
passing `EXTRAS="-ltinfo"` to the make command.

So the full command becomes:

```
$ make EXTRAS="-ltinfo"
# make install
```

#### I can't find the vainglorious command after installing!
The resulting executable after running the above commands is
called `vain`, not `vainglorious`, so you don't have to type so much.

```
$ vain
```

#### "Error opening scroll! Please check file ownership!" when starting vain
Your user does somehow not have the right permissions to view the scroll
file that is the source of the scrolling text that is shown when using
the program. This should be fixed in the newest version of the Makefile,
but you can fix it yourself by running

```
chmod 644 /usr/share/vainglorious/default.scroll
```

(assuming you didn't change any of the compilation flags)
