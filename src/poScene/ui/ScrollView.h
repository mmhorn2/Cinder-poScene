#pragma once

#include "poScene/View.h"

namespace po
{
	namespace scene
	{
		namespace ui
		{
			class ScrollView;
			typedef std::shared_ptr<ScrollView> ScrollViewRef;

			class ScrollViewDelegate;
			typedef std::shared_ptr<ScrollViewDelegate> ScrollViewDelegateRef;

			class ScrollViewDelegate
			{
				public:
					virtual void didStartScrolling( ScrollViewRef scrollView ) = 0;
					virtual void didScroll( ScrollViewRef scrollView ) = 0;
					virtual void didFinishScrolling( ScrollViewRef scrollView ) = 0;
			};

			class ScrollView : public po::scene::View
			{
				public:
					static ScrollViewRef create();

					void setContentOffset( ci::vec2 offset, bool bAnimate = false );
					void setDelegate( ScrollViewDelegateRef delegate ) { mDelegate = delegate; };

					po::scene::ViewRef getContentView() { return mContentView; }
					ci::vec2 getContentOffset() { return mContentView->getPosition(); }
					ci::vec2 getScrollTargetPos() { return mScrollTargetPos; }

					View& addSubview( ViewRef view, bool localize = false ) override;

					void setHorizontalScrollingLocked( bool shouldLock );
					void setVerticalScrollingLocked( bool shouldLock );
					void setThrowFactor( ci::vec2 throwFactor ) {mThrowFactor = throwFactor;}
					void setHorizontalSnapping( bool shouldSnap ) { mHorizontalSnappingEnabled = shouldSnap; };
					void setVerticalSnapping( bool shouldSnap ) { mVerticalSnappingEnabled = shouldSnap; };

					void enableMouseEvents();
					void disableMouseEvents();
					void enableTouchEvents();
					void disableTouchEvents();

				protected:
					ScrollView();

					void setup();
					void update();

					bool mInitialized;

					po::scene::ViewRef mContentView;

					// Scrolling
					ci::vec2 getSnapPos( ci::vec2 pos );
					bool mHorizontalSnappingEnabled, mVerticalSnappingEnabled;

					bool mHorizontalScrollingEnabled, mVerticalScrollingEnabled;
					bool mHorizontalScrollingLocked, mVerticalScrollingLocked;

					int mEventId;
					ci::vec2 mStartEventPos, mCurEventPos, mPrevEventPos;
					bool mIsScrolling;
					ci::vec2 mScrollTargetPos;
					float mMaxAccel;
					float mDecel;
					ci::vec2 mThrowFactor;

					std::weak_ptr<ScrollViewDelegate> mDelegate;

					// Event handlers
					// Note: in some cases, eventMoved pos is same as eventEnded
					// override and calculate the accel when eventMoved
					// then apply when eventEnded

					virtual void eventBeganInside( int id, ci::vec2 pos );
					virtual void eventMoved( int id, ci::vec2 pos );
					virtual void eventEnded( int id, ci::vec2 pos );

					ci::signals::ConnectionList mMouseConnections;
					bool mMouseEventsEnabled;
					void mouseDownInside( po::scene::MouseEvent& event );
					void mouseDrag( po::scene::MouseEvent& event );
					void mouseUp( po::scene::MouseEvent& event );

					ci::signals::ConnectionList mTouchConnections;
					bool mTouchEventsEnabled;
					void touchBeganInside( po::scene::TouchEvent& event );
					void touchMoved( po::scene::TouchEvent& event );
					void touchEnded( po::scene::TouchEvent& event );
			};
		}
	}
}
