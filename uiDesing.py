# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'testXhWgxo.ui'
##
## Created by: Qt User Interface Compiler version 5.15.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *

from mplwidget import MplWidget

import icons_rc

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1056, 718)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayout_3 = QVBoxLayout(self.centralwidget)
        self.verticalLayout_3.setSpacing(0)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.frame_2 = QFrame(self.centralwidget)
        self.frame_2.setObjectName(u"frame_2")
        self.frame_2.setStyleSheet(u"background: rgba(0, 0, 0, 0.3);")
        self.frame_2.setFrameShape(QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QFrame.Raised)
        self.verticalLayout_2 = QVBoxLayout(self.frame_2)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.stackedWidget = QStackedWidget(self.frame_2)
        self.stackedWidget.setObjectName(u"stackedWidget")
        self.stackedWidget.setStyleSheet(u"")
        self.home = QWidget()
        self.home.setObjectName(u"home")
        self.verticalLayout_6 = QVBoxLayout(self.home)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.frame_4 = QFrame(self.home)
        self.frame_4.setObjectName(u"frame_4")
        self.frame_4.setLayoutDirection(Qt.LeftToRight)
        self.frame_4.setAutoFillBackground(False)
        self.frame_4.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.frame_4.setFrameShape(QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QFrame.Raised)
        self.verticalLayout_5 = QVBoxLayout(self.frame_4)
        self.verticalLayout_5.setSpacing(10)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(5, 5, 5, 5)
        self.label = QLabel(self.frame_4)
        self.label.setObjectName(u"label")
        self.label.setMaximumSize(QSize(16777215, 100))
        font = QFont()
        font.setFamily(u"MS PGothic")
        font.setPointSize(24)
        self.label.setFont(font)
        self.label.setStyleSheet(u"color: rgb(255, 255, 255);")
        self.label.setAlignment(Qt.AlignCenter)

        self.verticalLayout_5.addWidget(self.label)

        self.label_2 = QLabel(self.frame_4)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setPixmap(QPixmap(u"icons/Rocket1.jpg"))
        self.label_2.setScaledContents(False)
        self.label_2.setAlignment(Qt.AlignCenter)

        self.verticalLayout_5.addWidget(self.label_2)

        self.btn_upload = QPushButton(self.frame_4)
        self.btn_upload.setObjectName(u"btn_upload")
        self.btn_upload.setMinimumSize(QSize(0, 100))
        font1 = QFont()
        font1.setFamily(u"MS PGothic")
        font1.setPointSize(20)
        font1.setBold(True)
        font1.setWeight(75)
        self.btn_upload.setFont(font1)
        self.btn_upload.setStyleSheet(u"QPushButton\n"
"{\n"
"	border-radius: 25px;\n"
"	background-color: rgb(255, 255, 255);\n"
"	color: rgb(0, 0, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color: rgb(135, 135, 203);\n"
"	color: rgb(0, 0, 0);\n"
"	\n"
"}")

        self.verticalLayout_5.addWidget(self.btn_upload)


        self.verticalLayout_6.addWidget(self.frame_4)

        self.stackedWidget.addWidget(self.home)
        self.graph = QWidget()
        self.graph.setObjectName(u"graph")
        self.graph.setStyleSheet(u"background: rgba(0, 0, 0, 0.5);")
        self.verticalLayout_4 = QVBoxLayout(self.graph)
        self.verticalLayout_4.setSpacing(0)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.frame_3 = QFrame(self.graph)
        self.frame_3.setObjectName(u"frame_3")
        self.frame_3.setStyleSheet(u"background: rgba(0, 0, 0, 0);")
        self.frame_3.setFrameShape(QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QFrame.Raised)
        self.verticalLayout = QVBoxLayout(self.frame_3)
        self.verticalLayout.setSpacing(10)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(5, 5, 5, 5)
        self.frame = QFrame(self.frame_3)
        self.frame.setObjectName(u"frame")
        self.frame.setStyleSheet(u"background-color: rgb(170, 170, 127);")
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout = QHBoxLayout(self.frame)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.MplWidget = MplWidget(self.frame)
        self.MplWidget.setObjectName(u"MplWidget")
        self.MplWidget.setStyleSheet(u"background-color: rgb(255, 170, 0);")

        self.horizontalLayout.addWidget(self.MplWidget)

        self.MplWidget_2 = MplWidget(self.frame)
        self.MplWidget_2.setObjectName(u"MplWidget_2")
        self.MplWidget_2.setStyleSheet(u"background-color: rgb(255, 170, 0);")

        self.horizontalLayout.addWidget(self.MplWidget_2)


        self.verticalLayout.addWidget(self.frame)

        self.frame_5 = QFrame(self.frame_3)
        self.frame_5.setObjectName(u"frame_5")
        self.frame_5.setMaximumSize(QSize(16777215, 50))
        self.frame_5.setFrameShape(QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_2 = QHBoxLayout(self.frame_5)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.lbl_acceleration = QLabel(self.frame_5)
        self.lbl_acceleration.setObjectName(u"lbl_acceleration")
        font2 = QFont()
        font2.setPointSize(15)
        self.lbl_acceleration.setFont(font2)
        self.lbl_acceleration.setStyleSheet(u"color: rgb(255, 255, 255);")
        self.lbl_acceleration.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_2.addWidget(self.lbl_acceleration)

        self.lbl_altitude = QLabel(self.frame_5)
        self.lbl_altitude.setObjectName(u"lbl_altitude")
        self.lbl_altitude.setFont(font2)
        self.lbl_altitude.setStyleSheet(u"color: rgb(255, 255, 255);")
        self.lbl_altitude.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_2.addWidget(self.lbl_altitude)


        self.verticalLayout.addWidget(self.frame_5)

        self.btn_graph = QPushButton(self.frame_3)
        self.btn_graph.setObjectName(u"btn_graph")
        self.btn_graph.setMinimumSize(QSize(0, 100))
        self.btn_graph.setFont(font1)
        self.btn_graph.setStyleSheet(u"QPushButton\n"
"{\n"
"	border-radius: 25px;\n"
"	background-color: rgb(255, 255, 255);\n"
"	color: rgb(0, 0, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color: rgb(135, 135, 203);\n"
"	color: rgb(0, 0, 0);\n"
"	\n"
"}")

        self.verticalLayout.addWidget(self.btn_graph)


        self.verticalLayout_4.addWidget(self.frame_3)

        self.stackedWidget.addWidget(self.graph)

        self.verticalLayout_2.addWidget(self.stackedWidget)


        self.verticalLayout_3.addWidget(self.frame_2)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        self.stackedWidget.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"Welcome to Rocket Flight Data Graphs", None))
        self.label_2.setText("")
        self.btn_upload.setText(QCoreApplication.translate("MainWindow", u"Upload File to Begin", None))
        self.lbl_acceleration.setText(QCoreApplication.translate("MainWindow", u"Altitude", None))
        self.lbl_altitude.setText(QCoreApplication.translate("MainWindow", u"Acceleration", None))
        self.btn_graph.setText(QCoreApplication.translate("MainWindow", u"Generate Graphs", None))
    # retranslateUi

