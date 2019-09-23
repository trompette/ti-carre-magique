Carré Magique
=============

This is the version 2 of a small game project I wrote a long time ago for my TI-89 calculator. The first version can be found on [ticalc.org](http://www.ticalc.org/archives/files/fileinfo/232/23253.html).

Building the game
-----------------

You first need to build a Docker image containing [TIGCC](http://tigcc.ticalc.org/linux/index.html):

    make docker-image

After that, you can compile the `carremag.89z` binary file:

    make

Running the game
----------------

Run the binary file on a real TI-89 calculator or use [TiEmu](http://lpg.ticalc.org/prj_tiemu/).

Licensing information
---------------------

Have a look at the LICENSE file.
