/***********************************************************************
*
* Copyright (c) 2021-2022 Barbara Geller and Ansel Sermersheim
*
* This example is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include <QtCore>
#include <QtGui>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QWidget* mainWindow = new QWidget();
   mainWindow->setMinimumSize(700, 350);

   QPushButton* pb = new QPushButton();
   pb->setText("Close");

   QSlider* sl = new QSlider(Qt::Orientation::Horizontal);
   sl->setTracking(false);

   QProgressBar* progress = new QProgressBar();

   QHBoxLayout* layout = new QHBoxLayout(mainWindow);
   layout->addWidget(pb);
   layout->addWidget(sl);
   layout->addWidget(progress);

   QObject::connect(pb, &QPushButton::clicked, mainWindow, &QWidget::close);

   mainWindow->show();

   return app.exec();
}

