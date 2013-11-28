TEMPLATE = subdirs

CONFIG += ordered static

SUBDIRS += qutty interface

qutty.file = ./qutty/QuTTY.pro


interface.depends = qutty

