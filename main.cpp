#include <QtCore>
#include <QtGui>

// tracking controls the behaviour of the slider updates.
// when set to true, all value-changes from the slider will be evaluated.
// when set to false, no events will be propagated when the slider is still held -
// only when the user releases the mouse button a single event will be processed.
constexpr bool tracking = true;

// if set to true, a percentage of completion value will be shown next to the progressbar
// no text output if set to false
constexpr bool show_percentage = false;

int main(int argc, char *argv[]) {

   // a qapplication for our eventloop needs
   QApplication app(argc, argv);

   // the main window widget, that containes all other widgets
   // we provide a new title for the main_window and specify a minimal
   // size requirement for ergonomic reasons
   auto* main_window = new QWidget();
   main_window->setMinimumSize(700, 100);
   main_window->setWindowTitle("QProgressBar Example");

   // create a new horizontal slider that we can use to set our values for the progressbar
   auto* slider = new QSlider(Qt::Orientation::Horizontal);
   slider->setTracking(tracking);

   // progressbar, that will mirror the state of slider
   // it copies the min and max range of the slider so the value
   // can be applied directly without additional math
   // also we disable the textual percent output; so the layout looks better
   auto* progress = new QProgressBar();
   progress->setMinimum(slider->minimum());
   progress->setMaximum(slider->maximum());
   progress->setValue(slider->minimum()); // MAYBE_BUG: this is required to show the text?
   progress->setTextVisible(show_percentage);

   // create a label, to show the value used for the progressbar
   auto* label = new QLabel();

   // set the window layout for vertical layouting
   // - placing ui elements vertically underneath each other
   auto* layout = new QVBoxLayout(main_window);
   layout->addWidget(slider);
   layout->addWidget(progress);
   layout->addWidget(label);
   layout->addStretch();

   // connect the slider to the progressbar
   // sets the value from the slider to the value of the progressbar
   QObject::connect(slider, &QSlider::valueChanged, progress, &QProgressBar::setValue);

   // set the value number to the label
   QObject::connect(slider, &QSlider::valueChanged, label, [label](int a) {label->setNum(a);});

   // display the components on screen
   main_window->show();

   // run the app eventloop
   return app.exec();
}

