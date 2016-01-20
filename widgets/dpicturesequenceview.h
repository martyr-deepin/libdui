#ifndef DPICTURESEQUENCEVIEW_H
#define DPICTURESEQUENCEVIEW_H

#include "libdui_global.h"
#include "dobject.h"

#include <QGraphicsView>

DUI_BEGIN_NAMESPACE

class DPictureSequenceViewPrivate;
class DPictureSequenceView : public QGraphicsView, public DObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DPictureSequenceView)
    D_DECLARE_PRIVATE(DPictureSequenceView)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(bool singleShot READ singleShot WRITE setSingleShot)

public:
    DPictureSequenceView(QWidget *parent = nullptr);

    void setPictureSequence(const QStringList &sequence);
    void play();

    int speed() const;
    void setSpeed(int speed);

    bool singleShot() const;
    void setSingleShot(bool singleShot);

Q_SIGNALS:
    void speedChanged(int speed) const;
    void playEnd() const;
};

DUI_END_NAMESPACE

#endif // DPICTURESEQUENCEVIEW_H
