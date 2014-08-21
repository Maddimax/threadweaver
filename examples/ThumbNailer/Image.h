#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QAtomicInt>
#include <QCoreApplication>

#include "Progress.h"

class Model;

/** @brief Image loads an image from a path, and then calculates and saves a thumbnail for it. */
class Image
{
    Q_DECLARE_TR_FUNCTIONS(Image)

public:
    enum Steps {
        Step_NotStarted,
        Step_LoadFile,
        Step_LoadImage,
        Step_ComputeThumbNail,
        Step_SaveImage,
        Step_NumberOfSteps = Step_SaveImage,
        Step_Complete = Step_SaveImage
    };

    Image(const QString inputFileName = QString(), const QString outputFileName = QString(),
          Model* model = 0, int id = 0);
    Progress progress() const;
    QString description() const;

    const QString inputFileName() const;
    const QString outputFileName() const;

    void loadFile();
    void loadImage();
    void computeThumbNail();
    void saveThumbNail();

private:
    void announceProgress();
    void error(Steps step, const QString& message);

    QString m_inputFileName;
    QString m_outputFileName;
    QAtomicInt m_progress;
    QAtomicInt m_failedStep;

    QByteArray m_imageData;
    QImage m_image;
    QImage m_thumbnail;
    Model* m_model;
    int m_id;
};

#endif // IMAGE_H