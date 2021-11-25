''' Senior Group Project Created for Rocket Data Graph
Data is saved to a text file and uploaded to show plots
sequentially
'''

# imports
import sys
import matplotlib
from matplotlib.figure import Figure
from matplotlib import animation
from matplotlib.backends.backend_qt5agg import (FigureCanvasQTAgg, NavigationToolbar2QT as NavigationToolbar)
from matplotlib.animation import FuncAnimation
from PyQt5 import QtWidgets, QtCore
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUiType


matplotlib.use('Qt5Agg')
# ui,_ = loadUiType('test.ui')
ui,_ = loadUiType('graph_data.ui')


class MainApp(QMainWindow, ui):
    def __init__(self):
        QMainWindow.__init__(self)
        self.setupUi(self)
        title = "Flight Data Visualization"
        self.setWindowTitle(title)
        self.pixmap = QPixmap('icons/Rocket1.jpg')
        self.label_2.setPixmap(self.pixmap)

        self.timeMillis, self.acceleration, self.altitude = [], [], []

        self.accel, = self.MplWidget.canvas.axes.plot([], [])
        self.alti, = self.MplWidget_2.canvas.axes.plot([], [])

        self.btn_upload.clicked.connect(self.open_dialog_box)
        self.btn_graph.clicked.connect(self.make_charts)
        self.btn_back.clicked.connect(self.home_screen)

    def make_charts(self):
        # Plot 1 Altitude
        self.MplWidget.canvas.axes.clear()
        self.MplWidget.canvas.axes.set_xlabel('Time (msec)')
        self.MplWidget.canvas.axes.set_ylabel('Altitude (m)')
        self.MplWidget.canvas.axes.set_title('Altitude Graph')

        self.alti, = self.MplWidget.canvas.axes.plot(self.timeMillis, self.altitude, 'r', lw=2)
        self.MplWidget.canvas.draw()

        # Plot 2 Acceleration
        self.MplWidget_2.canvas.axes.clear()
        self.MplWidget_2.canvas.axes.set_xlabel('Time (msec)')
        self.MplWidget_2.canvas.axes.set_ylabel('Acceleration (m/s)')
        self.MplWidget_2.canvas.axes.set_title('Acceleration Graph')

        self.accel, = self.MplWidget_2.canvas.axes.plot(self.timeMillis, self.acceleration, 'r', lw=2)
        self.MplWidget_2.canvas.draw()

        self.lbl_altitude.setText(f'Highest Acceleration: {max(self.acceleration)} (m/s)')
        self.lbl_acceleration.setText(f'Highest Altitude: {max(self.altitude)} (m)')

        self.anim_alt = animation.FuncAnimation(self.MplWidget, self.animate_altitude, interval=100)
        self.anim_accel = animation.FuncAnimation(self.MplWidget_2, self.animate_acceleration, interval=100)

        self.show()

    def home_screen(self):
        self.lbl_altitude.setText(f'Acceleration: (m/s)')
        self.lbl_acceleration.setText(f'Altitude: (m)')
        for i in range(len(self.timeMillis)):
            self.acceleration.pop(-1)
            self.altitude.pop(-1)
            self.timeMillis.pop(-1)
        self.MplWidget.canvas.axes.clear()
        self.MplWidget_2.canvas.axes.clear()
        self.stackedWidget.setCurrentWidget(self.home)
        return self.acceleration, self.altitude, self.timeMillis

    def open_dialog_box(self):
        filename = QFileDialog.getOpenFileName()
        path = filename[0]
        print(path)

        with open(path, 'r') as f:
            data = f.readlines()

            for line in data:
                acc = line[14:17]
                alt = line[79:82]
                t = line[88:-1]
                self.acceleration.append(acc)
                self.altitude.append(alt)
                self.timeMillis.append(t)

        self.acceleration.pop(-1)
        self.altitude.pop(-1)
        self.timeMillis.pop(-1)

        for i in range(len(self.acceleration)):
            self.acceleration[i] = int(self.acceleration[i])

        for i in range(len(self.altitude)):
            self.altitude[i] = int(self.altitude[i])

        for i in range(len(self.timeMillis)):
            self.timeMillis[i] = int(self.timeMillis[i])

        print(self.acceleration)
        print(self.altitude)
        print(self.timeMillis)

        self.stackedWidget.setCurrentWidget(self.graph)

    def animate_acceleration(self, i):
        self.accel.set_data(self.timeMillis[:i], self.acceleration[:i])
        return self.accel,

    def animate_altitude(self, i):
        self.alti.set_data(self.timeMillis[:i], self.altitude[:i])
        return self.alti,


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    app.exec_()


if __name__ == '__main__':
    main()
