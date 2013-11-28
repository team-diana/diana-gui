TEMPLATE = subdirs

CONFIG += ordered static

SUBDIRS += diana-qutty interface

qutty.file = ./qutty/QuTTY.pro


interface.depends = qutty

