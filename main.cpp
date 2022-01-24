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

// handler event generator function; to not spam around long lambdas
// also reduce some code duplication
auto produce_color_button_handler(QPalette::ColorRole group, QProgressBar* progress) {
   
   return [group, progress]() {

      // aquire the old palette and color
      const auto& active_palette = progress->palette();
      QColor previous = active_palette.color(group);

      // let the user select a new color
      // the preselected color will be the used color
      // this allows minor adjustments w/o a lot of guesswork
      // an screencapture to get the color code...
      QColor color;
      color = QColorDialog::getColor(previous);

      // when the selected color is valid, we set it 
      // as the new color, invalid if user cancelled the dialog
      if (color.isValid()) {
         // create a new palette
         QPalette new_palette{};
         new_palette.setColor(group, color);
         // apply the new palette
         // the widget will automatically merge the palette
         // to get the final used palette
         progress->setPalette(new_palette);
         progress->setForegroundRole(QPalette::Highlight);
         progress->setBackgroundRole(QPalette::Base);
      }
   };

}

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

   // construct a pair of buttons to set the color palette of a QProgressBar
   // to test the dynamic styling abilities
   auto* foreground_button = new QPushButton("Foreground Color");
   auto* background_button = new QPushButton("Background Color");

   // create a label, to show the value used for the progressbar
   auto* label = new QLabel();
   label->setNum(slider->minimum());

   auto* toolbar_layout = new QHBoxLayout();
   toolbar_layout->addWidget(foreground_button);
   toolbar_layout->addWidget(background_button);
   toolbar_layout->addWidget(label);
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

   // set the color when a button was clicked
   QObject::connect(foreground_button, &QPushButton::clicked, progress, produce_color_button_handler(QPalette::Highlight, progress));
   QObject::connect(background_button, &QPushButton::clicked, progress, produce_color_button_handler(QPalette::Base, progress));

   // display the components on screen
   main_window->show();

   // run the app eventloop
   return app.exec();
}

