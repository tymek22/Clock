//
//  ViewController.h
//  Clock
//
//  Copyright © 2019 Tymek Feldman. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreBluetooth/CBService.h>

CBUUID *uuidTime = nil;
CBUUID *uuidColor = nil;
CBUUID *uuidTimeChar = nil;
CBUUID *uuidColorChar = nil;
NSTimer *timer;

@interface ViewController : UIViewController <CBCentralManagerDelegate, CBPeripheralDelegate>

@property (nonatomic, strong) CBCentralManager *myCentralManager;
@property (nonatomic, strong) CBPeripheral *myPeripheral;
@property (nonatomic, strong) CBService *timeService;
@property (nonatomic, strong) CBService *colorService;
@property (nonatomic, strong) CBCharacteristic *colorCharacteristic;
@property (nonatomic, strong) CBCharacteristic *timeCharacteristic;
- (void) centralManagerDidUpdateState:(CBCentralManager *)central;

- (IBAction)connectBLE:(id)sender;
- (IBAction)disconnectBLE:(id)sender;
- (IBAction)enterDFU:(id)sender;
- (IBAction)setCurTime:(id)sender;
- (IBAction)setCusTime:(id)sender;
- (IBAction)colorSlider:(id)sender;
- (IBAction)lampOff:(id)sender;
- (IBAction)alphaChange:(id)sender;
- (IBAction)setLamp:(id)sender;

@property (weak, nonatomic) IBOutlet UILabel *textLabel;
@property (weak, nonatomic) IBOutlet UIButton *connectButton;
@property (weak, nonatomic) IBOutlet UIButton *disconnectButton;
@property (weak, nonatomic) IBOutlet UIButton *dfuButton;
@property (weak, nonatomic) IBOutlet UILabel *lampLabel;
@property (weak, nonatomic) IBOutlet UILabel *pirLabel;
@property (weak, nonatomic) IBOutlet UILabel *ldrLabel;
@property (weak, nonatomic) IBOutlet UILabel *tempLabel;
@property (weak, nonatomic) IBOutlet UISwitch *lampSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *pirSwitch;
@property (weak, nonatomic) IBOutlet UIProgressView *ldrBar;
@property (weak, nonatomic) IBOutlet UILabel *tempLabel2;
@property (weak, nonatomic) IBOutlet UIButton *setCurTimeButton;
@property (weak, nonatomic) IBOutlet UIButton *setCusTimeButton;
@property (weak, nonatomic) IBOutlet UISlider *colorUISlider;
@property (weak, nonatomic) IBOutlet UIImageView *colorScaleImage;
@property (weak, nonatomic) IBOutlet UIImageView *colorChosenImage;
@property (weak, nonatomic) IBOutlet UIImageView *imageBackground;
@property (weak, nonatomic) IBOutlet UIButton *lampOffButton;
@property (weak, nonatomic) IBOutlet UISlider *alphaSlider;
@property (weak, nonatomic) IBOutlet UIImageView *alphaImage;
@property (weak, nonatomic) IBOutlet UIButton *setLampButton;

@end

