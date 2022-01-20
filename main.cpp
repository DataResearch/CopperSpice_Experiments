#include <QtCore>
#include <QtGui>

constexpr bool tracking = true;

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QWidget* mainWindow = new QWidget();
   mainWindow->setMinimumSize(700, 350);
   mainWindow->setWindowTitle("QProgressBar Example");

   QSlider* sl = new QSlider(Qt::Orientation::Horizontal);
   sl->setTracking(tracking);

   QProgressBar* progress = new QProgressBar();
   progress->setMinimum(sl->minimum());
   progress->setMaximum(sl->maximum());

   QHBoxLayout* layout = new QHBoxLayout(mainWindow);
   layout->addWidget(sl);
   layout->addWidget(progress);

   QObject::connect(sl, &QSlider::valueChanged, progress, &QProgressBar::setValue);

   mainWindow->show();

   return app.exec();
}

