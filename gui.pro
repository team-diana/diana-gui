TEMPLATE = subdirs

CONFIG += ordered static

SUBDIRS += diana-qutty interface

qutty.file = ./diana-qutty/diana-qutty.pro


interface.depends = diana-qutty

