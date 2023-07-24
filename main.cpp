#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsBlurEffect>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create main window
    QMainWindow mainWindow;
    QWidget *centralWidget = new QWidget;
    mainWindow.setCentralWidget(centralWidget);

    // Create widgets
    QLabel *imageLabel = new QLabel;
    QSlider *slider = new QSlider(Qt::Horizontal);
    QPushButton *openButton = new QPushButton("Open Image");

    // Set up layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(slider);
    mainLayout->addWidget(openButton);

    QObject::connect(openButton, &QPushButton::clicked, [&imageLabel]() {
        QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image", QString(),
                                                        "Image Files (*.png *.jpg *.bmp)");
        if (!filePath.isEmpty()) {
            QImage image(filePath);
            if (!image.isNull()) {
                imageLabel->setPixmap(QPixmap::fromImage(image));
            }
        }
    });

    QObject::connect(slider, &QSlider::valueChanged, [&imageLabel](int blurRadius) {
        QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
        blurEffect->setBlurRadius(blurRadius);
        imageLabel->setGraphicsEffect(blurEffect);
    });

    // Show the main window
    mainWindow.show();

    return app.exec();
}
