#include "scene.h"

Scene::Scene(QObject *parent):
    QGraphicsScene(parent)
{
    init();
}

Scene::Scene(const QRectF &sceneRect, QObject *parent):
    QGraphicsScene(sceneRect, parent)
{
    init();
}

Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent):
    QGraphicsScene(x, y, width, height, parent)
{
    init();
}

void Scene::init()
{
    isPressing_ = false;
    root_ = 0;

    // Disable the scene size adaptation to items rect with a non null rect.
    setSceneRect(0, 0, 0, 1);

    selection_.setRect(0, 0, 0, 0);
    addItem(&selection_);
}

void Scene::clear()
{
    if(root_)
        delete root_;

    selectedRegions_.clear();
    root_ = 0;
}

void Scene::clearSelection()
{
    QGraphicsItem *child;
    RegionItem *regionItem;

    // Unselect all items.
    foreach(child, selectedRegions_)
    {
        regionItem = static_cast<RegionItem *>(child);
        regionItem->unselect();
    }

    baseSelection_.clear();
    selectedRegions_.clear();
    emit selectionCleared();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !isPressing_)
    {
        isPressing_ = true;

        pressPos_ = event->scenePos();
        selection_.show();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isPressing_)
    {
        // Adapt if the selection rectangle has a negative size.
        if(pressPos_.x() < event->scenePos().x())
            selection_.setRect(pressPos_.x(), 0, event->scenePos().x()-pressPos_.x(), 0);
        else
            selection_.setRect(event->scenePos().x(), 0, pressPos_.x()-event->scenePos().x(), 0);

        if(pressPos_.y() < event->scenePos().y())
            selection_.setRect(selection_.rect().x(), pressPos_.y(), selection_.rect().width(), event->scenePos().y()-pressPos_.y());
        else
            selection_.setRect(selection_.rect().x(), event->scenePos().y(), selection_.rect().width(), pressPos_.y()-event->scenePos().y());
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
      {
          isPressing_ = false;

          // Redraw all items in selection.
          if(root_)
          {
              clearSelection();

              // Check if it is a click.
              if(selection_.rect().width() * selection_.rect().height() == 0)
                  select(event->scenePos());
              else
                  select(selection_.rect());

              emit newSelection(selectedRegions_);
          }

          selection_.setRect(0, 0, 0, 1);
          selection_.hide();
      }
}

void Scene::select(QGraphicsItem *root, const QPointF& point, const QRectF& rect)
{
    QGraphicsItem *child;
    RegionItem *regionItem;

    // Check if it is a click.
    if(!point.isNull())
    {
        foreach(child, root->childItems())
        {
            regionItem = static_cast<RegionItem *>(child);

            if(regionItem->contains(point))
            {
                regionItem->select();
                selectedRegions_ << regionItem;
            }
        }
    }

    else
    {
        foreach(child, root->childItems())
        {
            regionItem = static_cast<RegionItem *>(child);

            if(regionItem->intersects(rect))
            {
                regionItem->select();
                selectedRegions_ << regionItem;
            }
        }
    }

    emit newSelection();
}

void Scene::select(const QList<RegionItem *>& selectedRegions)
{
    RegionItem *child;
    foreach(child, selectedRegions)
    {
        if(!child->isSelected())
        {
            child->select();
            selectedRegions_ << child;
        }
    }

    ensureVisible(selectedRegions_.last());
    emit newSelection();
}

void Scene::unselect(const QList<RegionItem *>& unselectedRegions)
{
    RegionItem *child;
    foreach(child, unselectedRegions)
    {
        if(child->isSelected())
        {
            child->unselect();
            selectedRegions_.removeOne(child);
        }
    }

    // Check if after the removal, the selected list isn't empty.
    if(!selectedRegions_.isEmpty())
        ensureVisible(selectedRegions_.last());
    emit newSelection();
}


void Scene::ensureVisible(QGraphicsItem *graphicalItem)
{
    QGraphicsView *view;
    foreach (view, views())
        view->ensureVisible(graphicalItem);
}

void Scene::setRoot(RootGraphicsItem *root)
{
    // Delete all items.
    clear();

    root_ = root;
    addItem(root);
}

void Scene::changeScene(const QString& filename, RootGraphicsItem *root)
{
    backgroundPath_ = filename;

    // Delete all items.
    clear();

    QPixmap pixmap(filename);
    setSceneRect(pixmap.rect());
    setBackgroundBrush(QBrush(pixmap));

    // Add new items.
    if(root)
    {
        root_ = root;
        addItem(root);
    }
}
