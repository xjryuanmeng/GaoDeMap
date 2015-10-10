//
//  ViewController.m
//  TestGaoDeMap
//
//  Created by libo on 15/9/18.
//  Copyright (c) 2015年 libo. All rights reserved.
//

#import "ViewController.h"
#import "GaoMapHeaders.h"
#import "OutSearchViewController.h"
#import "OutBottomView.h"
#import "OutNaviViewController.h"

@interface ViewController ()<MAMapViewDelegate>

@property (nonatomic ,strong) GaoMapView *mapview;

@property (nonatomic ,strong) OutBottomView *detailView;

@property (nonatomic ,strong)  UIView *searchBar;

@property (nonatomic ,strong) OutNaviViewController *naviVC;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[GaoMapConfig sharedConfig] setup];
    
    [self addMap];
    
    [self addSearchView];
    
    [self addOutShowView];
    
    [self addOutNaviView];
}

-(void)addMap
{
    self.mapview = [GaoMapView getMapViewWithFrame:CGRectMake(0, 0, GAO_SIZE.width, GAO_SIZE.height) parentView:self.view];
    [self.mapview.mapManager showUserLocationPoint];
    [self.mapview defaultSetting];
    
    __weak ViewController *weakself = self;
    self.mapview.mapManager.clickedAnnotation = ^(id<MAAnnotation> annotation, MAAnnotationView *annotationView){
        if(annotation == nil){
            [weakself showOutDetailView:NO];
        }else {
            [weakself.detailView refreshWithData:annotation type:OutBottomTypeDest];
            [weakself showOutDetailView:YES];
        }
    };
}

-(void)addSearchView
{
    self.searchBar = [[UIView alloc] initWithFrame:CGRectMake(10, 30, GAO_SIZE.width - 20, 44)];
    self.searchBar.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:self.searchBar];
    
    UIButton *btn1 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    btn1.frame = CGRectMake(50,0, 80, 44);
    btn1.backgroundColor = [UIColor redColor];
    [btn1 setTitle:@"搜索" forState:UIControlStateNormal];
    [btn1 addTarget:self action:@selector(redBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.searchBar addSubview:btn1];
    
    UIButton *btn2 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    btn2.frame = CGRectMake(140,0, 80, 44);
    btn2.backgroundColor = [UIColor blueColor];
    [btn2 setTitle:@"品牌墙" forState:UIControlStateNormal];
    [btn2 addTarget:self action:@selector(blueBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.searchBar addSubview:btn2];
    
    self.mapview.logoCenter = self.searchBar.center;
}

-(void)addOutShowView
{
    self.detailView = [OutBottomView addViewOn:self.view marginBottom:15 marginLeft:10];
    [self.detailView refreshWithData:nil type:OutBottomTypeDest];
    
    __weak ViewController *weakself = self;
    self.detailView.btnClicked = ^(UIButton *btn){
        NSLog(@"带我去");
        weakself.searchBar.hidden = YES;
       
        weakself.naviVC.show = YES;
    };
    
    [self showOutDetailView:NO];
}

-(void)addOutNaviView
{
    self.naviVC = [[OutNaviViewController alloc] init];
    [self addChildViewController:_naviVC];
    [self.view addSubview:_naviVC.view];
    
    _naviVC.show = NO;
}

#pragma mark - Action

-(void)showOutDetailView:(BOOL)show
{
    self.detailView.hidden = !show;
    
    [self.mapview setOutBtnBottomMargin:self.detailView.myHeight + 40 animation:YES];
}

-(void)redBtnClicked:(UIButton *)btn
{
    NSLog(@"进入搜索");
    OutSearchViewController *search = [[OutSearchViewController alloc] init];
    search.map = self.mapview;
    [self.navigationController pushViewController:search animated:YES];
}

-(void)blueBtnClicked:(UIButton *)btn
{
    NSLog(@"进入品牌墙");
}


-(void)viewWillAppear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:YES animated:YES];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:NO animated:YES];
}


@end