//
//  GaoMapSearchManager.h
//  TestGaoDeMap
//
//  Created by libo on 15/9/30.
//  Copyright (c) 2015年 libo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <AMapSearchKit/AMapCommonObj.h>

@class GaoMapView;

typedef void (^GaoBaseBlock) ();

/**
 *  搜索结果返回
 *
 *  @param count      数量
 *  @param pois       AMapPOI
 *  @param suggestion 建议信息
 */
typedef void(^SearchFinished)(NSError *error,  NSArray *pois, AMapSuggestion *suggestion);

/**
 *  交通搜索结果返回
 *
 *  @param count      数量
 *  @param pois       AMapPOI
 *  @param suggestion 建议信息
 */
typedef void(^NaviSearchFinished)(NSError *error, AMapRoute *route);

/**
 *  输入提示 结果返回
 *  tips为 AMapTip
 */
typedef void(^InputTipsFinished)(NSError *error, NSArray *tips);

/**
 *  地理编码 结果返回
 *  数组元素为AMapGeocode
 **/
typedef void(^GeoFinished)(NSError *error, NSArray *geocodes);

/**
 *  地理逆编码 结果返回
 *  数组元素为AMapReGeocode
 **/
typedef void(^RevserGeoFinished)(NSError *error, AMapReGeocode *res);

/**
 *  地图搜索、导航等的内容管理
 */

@interface GaoMapSearchManager : NSObject

+(GaoMapSearchManager *)getSearchManager;

@property (nonatomic , weak) GaoMapView *map;

#pragma mark - 搜索

/**
 *  根据ID搜索POI
 */
-(void)searchPOIById:(NSString *)uid finish:(SearchFinished)block;

/**
 *  关键字搜索
 */
/* 根据关键字来搜索POI. */
- (void)searchPOIByKeyword:(NSString *)keywords cityCode:(NSString *)cityCode finish:(SearchFinished)block;

/**
 *  周边搜索
 */
- (void)searchPOIArroundByKeywords:(NSString *)keywords location:(CLLocationCoordinate2D)coor radius:(NSInteger)radius finish:(SearchFinished)block;

/**
 *  多边形搜索
 *  points元素为AMapGeoPoint
 */
-(void)searchPOIByKewords:(NSString *)keywords polygons:(NSArray *)points finish:(SearchFinished)block;

#pragma mark - 导航

/**
 *  公交导航搜索
 *  strategy 公交换乘策略：0-最快捷模式；1-最经济模式；2-最少换乘模式；3-最少步行模式；4-最舒适模式；5-不乘地铁模式
 */
-(void)searchNaviBusWithStart:(AMapGeoPoint *)start dest:(AMapGeoPoint *)dest strategy:(NSInteger)strategy cityCode:(NSString *)cityCode finish:(NaviSearchFinished)block;

/**
 *  步行导航搜索
 */
-(void)searchNaviWalkWithStart:(AMapGeoPoint *)start dest:(AMapGeoPoint *)dest  finish:(NaviSearchFinished)block;

/**
 *  驾车导航搜索
 *  strategy 驾车导航策略：0-速度优先（时间）；1-费用优先（不走收费路段的最快道路）；2-距离优先；3-不走快速路；4-结合实时交通（躲避拥堵）；5-多策略（同时使用速度优先、费用优先、距离优先三个策略）；6-不走高速；7-不走高速且避免收费；8-躲避收费和拥堵；9-不走高速且躲避收费和拥堵
 */
-(void)searchNaviDriveWithStart:(AMapGeoPoint *)start dest:(AMapGeoPoint *)dest strategy:(NSInteger)strategy finish:(NaviSearchFinished)block;


#pragma mark - 输入提示

/**
 *  获取输入提示
 *
 *  @param keywords
 *  @param cityName 城市名或城市code
 */
-(void)inputTipsWithKeywords:(NSString *)keywords city:(NSString *)cityName finish:(InputTipsFinished)block;


#pragma mark - 地理编码 

/**
 * 根据 名称 搜索地理位置
 * @param name必选
 * @param cityName可选（可为城市名、code,adcode）
 */
-(void)geoSearchByName:(NSString *)name city:(NSString *)cityName finish:(GeoFinished)block;

/**
 *  根据经纬度查地名
 */
-(void)reverseGeoSearchByCoor:(CLLocationCoordinate2D)coor finish:(RevserGeoFinished)block;

#pragma mark - 云图POI
/**
 *  本地检索
 *  city为必选
 *  refresh为YES刷新，NO为加载更多
 */
-(void)searchCloudPOIWithCity:(NSString *)city keywords:(NSString *)key isRefresh:(BOOL)refresh finish:(SearchFinished)block;

/**
 *  POI ID检索
 *  city为必选
 *  refresh为YES刷新，NO为加载更多
 */
-(void)searchCloudPOIWithID:(NSInteger)ID finish:(SearchFinished)block;

/**
 *  搜索周边POI
 *
 *  @param coor 中心点
 *  @param key  可选关键字
 */
- (void)searchCloudPOIWithPoint:(CLLocationCoordinate2D)coor keywords:(NSString *)key isRefresh:(BOOL)refresh finish:(SearchFinished)block;

@end
