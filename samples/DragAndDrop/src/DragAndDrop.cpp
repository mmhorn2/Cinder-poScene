#include "DragAndDrop.h"

#include "poScene/DraggableView.h"

DragAndDropRef DragAndDrop::create() 
{
    DragAndDropRef view(new DragAndDrop());
    view->setup();
    return view;
}

DragAndDrop::DragAndDrop()
{
}

void DragAndDrop::setup() 
{
	mView->addChild(po::scene::DraggableView::create());
}
