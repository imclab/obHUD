# Copyright (c) 2011, Kevin Porter
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#    *  Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#    *  Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#    *  Neither the name of Ryan Flannery nor the names of his contributors
#       may not be used to endorse or promote products derived from this
#       software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

BINDIR=/usr/local/bin
MANDIR=/usr/local/man/man1

# build flags
CFLAGS=`xosd-config --cflags` -c
LIBS=`xosd-config --libs`

### build clock
clock: clock.o
	/usr/bin/cc $(LIBS) -o $@ clock.o

clock.o: clock.c
	/usr/bin/cc $(CFLAGS) clock.c

test: test.o
	/usr/bin/cc $(LIBS) -o $@ test.o

test.o: test.c
	/usr/bin/cc $(CFLAGS) test.c

### isntalls to the bindir/mandir of choice
install: clock clock.1
	/usr/bin/install -c -m 0555 clock   $(BINDIR)
	/usr/bin/install -c -m 0444 clock.1 $(MANDIR)

### remove any installed instance of the target
uninstall:
	rm -f $(BINDIR)/clock
	rm -f $(MANDIR)/clock.1

### removes target and any intermediate build files
clean:
	rm -f clock.o clock

