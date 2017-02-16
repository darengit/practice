obj-m += helloworld.o
CUR = $(shell uname -r)
DIR = /lib/modules/$(CUR)/build

all:
	$(MAKE) -C $(DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(DIR) M=$(PWD) clean
