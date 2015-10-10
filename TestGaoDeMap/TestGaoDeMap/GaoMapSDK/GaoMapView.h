//
//  GaoMapView.h
//  TestGaoDeMap
//
//  Created by libo on 15/9/29.
//  Copyright (c) 2015年 libo. All rights reserved.
//

#import <AMapNaviKit/AMapNaviKit.h>

@class GaoMapManager;
@class GaoMapSearchManager;
@class AMapTip;

@interface GaoMapView : MAMapView

+(GaoMapView *)getMapViewWithFrame:(CGRect)frame parentView:(UIView *)parentView;

-(void)defaultSetting;

@property (nonatomic ,readonly, strong) GaoMapManager *mapManager;

@property (nonatomic ,readonly, strong) GaoMapSearchManager *searchManager;

-(void)testNavi;

/**
 *  设置定位icon、缩放icon与地图底部的间距
 */
-(void)setOutBtnBottomMargin:(float)bottom animation:(BOOL)animated;

/**
 *  标注AMapTip
 */
-(void)addMyAnnotationTip:(AMapTip *)tip;

/**
 *  标注AMapPOI
 */
-(void)addMyAnnotationPois:(NSArray *)pois;

/**
 *  普通标注 GaoBaseAnnotation
 **/
- (void)addMyAnnotationBase:(NSArray *)annotations;

/**
 *  清理map上的annotation和overlay等
 */
- (void)cleanMapView;

/**
 *  释放mapView
 */
- (void)deallocMapView;


@end
