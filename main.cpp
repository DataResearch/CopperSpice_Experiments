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
   progress->setValue(slider->minimum());
   progress->setTextVisible(show_percentage);

   // create a label, to show the value used for the progressbar
   auto* label = new QLabel();
   label->setNum(slider->minimum());

   // a button that should close our application
   auto* close_button = new QPushButton("Close");

   // a button that reduces our value by 10
   auto* backwards_button = new QPushButton("-10");

   // a button that advances our value by 10
   auto* forwards_button = new QPushButton("+10");

      // a button that reduces our value by 1
   auto* single_backwards_button = new QPushButton("-1");

   // a button that advances our value by 1
   auto* single_forwards_button = new QPushButton("+1");

   // magic toolbar layouts
   auto* toolbar_layout = new QHBoxLayout();
   toolbar_layout->addWidget(label);
   toolbar_layout->addWidget(close_button);
   toolbar_layout->addWidget(backwards_button);
   toolbar_layout->addWidget(forwards_button);
   toolbar_layout->addWidget(single_backwards_button);
   toolbar_layout->addWidget(single_forwards_button);
   toolbar_layout->addStretch();

   // set the window layout for vertical layouting
   // - placing ui elements vertically underneath each other
   auto* layout = new QVBoxLayout(main_window);
   layout->addWidget(slider);
   layout->addWidget(progress);
   layout->addLayout(toolbar_layout);
   layout->addStretch();

   // connect the slider to the progressbar
   // sets the value from the slider to the value of the progressbar
   QObject::connect(slider, &QSlider::valueChanged, progress, &QProgressBar::setValue);

   // set the value number to the label
   QObject::connect(slider, &QSlider::valueChanged, label, [label](int a) {label->setNum(a);});

   // close button
   QObject::connect(close_button, &QPushButton::clicked, main_window, &QWidget::close);

   // reduce value by 10 button event
   QObject::connect(backwards_button, &QPushButton::clicked, slider, [slider]() {
      const auto current_value = slider->value();
      slider->setValue(current_value - 10);
   });

   // add value by 10 button event
   QObject::connect(forwards_button, &QPushButton::clicked, slider, [slider]() {
      const auto current_value = slider->value();
      slider->setValue(current_value + 10);
   });

   // reduce value by 1 button event
   QObject::connect(single_backwards_button, &QPushButton::clicked, slider, [slider]() {
      const auto current_value = slider->value();
      slider->setValue(current_value - 1);
   });

   // add value by 1 button event
   QObject::connect(single_forwards_button, &QPushButton::clicked, slider, [slider]() {
      const auto current_value = slider->value();
      slider->setValue(current_value + 1);
   });

   // display the components on screen
   main_window->show();

   // run the app eventloop
   return app.exec();
}

