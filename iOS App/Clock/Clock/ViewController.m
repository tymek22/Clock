//
//  ViewController.m
//  Clock
//
//  Copyright © 2019 Tymek Feldman. All rights reserved.
//

#import "ViewController.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreBluetooth/CBService.h>

@interface ViewController ()

@end

@implementation ViewController

bool connectedToDevice = false;
bool servicesDone = false;
bool btPoweredOn = false;
int redInt = 0;
int greenInt = 0;
int blueInt = 0;


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSLog(@"App started");
    uuidTime =          [CBUUID UUIDWithString:@"AAB4D357-02A9-4509-A4A3-C11BE4AC09EE"];
    uuidColor =         [CBUUID UUIDWithString:@"AAB4D357-02A9-4509-A4A3-C11BE4AC09F2"];
    uuidTimeChar =      [CBUUID UUIDWithString:@"AAB4D357-02A9-4509-A4A3-C11BE4AC09EF"];
    uuidColorChar =     [CBUUID UUIDWithString:@"AAB4D357-02A9-4509-A4A3-C11BE4AC09F3"];
}

- (IBAction)connectBLE:(id)sender {
    // Connect button pressed, initialize bluetooth
    _connectButton.hidden = true;
    _myCentralManager = [[CBCentralManager alloc] initWithDelegate:self queue:nil options:nil];
    NSLog(@"Init done");
}

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    // You should test all scenarios
    if (central.state != CBManagerStatePoweredOn) {
        NSLog(@"Bluetooth is off");
        _textLabel.text = @"Turn on bluetooth";
        _connectButton.hidden = false;
        return;
    }
    
    if (central.state == CBManagerStatePoweredOn) {
        // Bluetooth is on, scan for devices
        NSLog(@"Scanning will start");
        _connectButton.hidden = true;
        btPoweredOn = true;
        [_myCentralManager scanForPeripheralsWithServices:nil options:@{ CBCentralManagerScanOptionAllowDuplicatesKey : @YES }];
        _textLabel.text = @"Scanning";
    }
}

- (void)centralManager:(CBCentralManager *)central
 didDiscoverPeripheral:(CBPeripheral *)peripheral
     advertisementData:(NSDictionary *)advertisementData
                  RSSI:(NSNumber *)RSSI{
    
    NSLog(@"Discovered %@", peripheral.name);
    if([peripheral.name  isEqual: @"Clock"]){
        // If bluetooth scan resulted in a device called "Clock", stop scanning and connect to it
        _myPeripheral = peripheral;
        [_myCentralManager stopScan];
        [_myCentralManager connectPeripheral:_myPeripheral options:nil];
        _textLabel.text = @"Connecting";
    }
}

- (void)centralManager:(CBCentralManager *)central  didConnectPeripheral:(CBPeripheral *)peripheral {
    connectedToDevice = true;
    NSLog(@"Peripheral connected");
    _myPeripheral.delegate = self;
    NSLog(@"Name of the device is: %@", _myPeripheral.name);
    NSString *tempString = [NSString stringWithFormat:@"Connected to %@", _myPeripheral.name];
    _textLabel.text = [NSString stringWithString:tempString];
    // If connected, start to discover the BT services
    [_myPeripheral discoverServices:nil];
}

- (void)peripheral:(CBPeripheral *)peripheral   didDiscoverServices:(NSError *)error {
    
    // Look at the discovered services and discover their characteristics
    for (CBService *service in peripheral.services) {
        NSLog(@"Discovered service %@", service);
        if([service.UUID isEqual:uuidTime]){
            _timeService = service;
            NSLog(@"Time discovered");
        }
        else if([service.UUID isEqual:uuidColor]){
            _colorService = service;
            NSLog(@"Color discovered");
        }
    }
    servicesDone = true;
    [peripheral discoverCharacteristics:nil forService:_colorService];
    [peripheral discoverCharacteristics:nil forService:_timeService];
}

- (void)peripheral:(CBPeripheral *)peripheral
didDiscoverCharacteristicsForService:(CBService *)service
             error:(NSError *)error {
    
    // If the characteristics are found, show the full UI with all buttons
    for (CBCharacteristic *characteristic in service.characteristics) {
        NSLog(@"Discovered characteristic %@", characteristic);
        if([characteristic.UUID isEqual:uuidColorChar]){
            NSLog(@"Found color characteristic");
            _colorCharacteristic = characteristic;
            _disconnectButton.hidden = false;
            _dfuButton.hidden = false;
            _lampLabel.hidden = false;
            _pirLabel.hidden = false;
            _ldrLabel.hidden = false;
            _tempLabel.hidden = false;
            _tempLabel2.hidden = false;
            _lampSwitch.hidden = false;
            _pirSwitch.hidden = false;
            _ldrBar.hidden = false;
            _colorUISlider.hidden = false;
            _colorScaleImage.hidden = false;
            _colorChosenImage.hidden = false;
            _imageBackground.hidden = false;
            _lampOffButton.hidden = false;
            _alphaImage.hidden = false;
            _alphaSlider.hidden = false;
            _setLampButton.hidden = false;
            
            // Also start a timer which reads data every second
            timer = [NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(readData) userInfo:nil repeats:YES];
        }
        else if([characteristic.UUID isEqual:uuidTimeChar]){
            NSLog(@"Found time characteristic");
            _timeCharacteristic = characteristic;
            _setCurTimeButton.hidden = false;
            _setCusTimeButton.hidden = false;
        }
    }
}

- (void) readData{
    [_myPeripheral readValueForCharacteristic:_colorCharacteristic];
}

- (IBAction)disconnectBLE:(id)sender {
    // Disconnect button pressed: disconnect from BT and hide UI
    [timer invalidate];
    [_myCentralManager cancelPeripheralConnection:_myPeripheral];
    NSLog(@"Device disconnected");
    _disconnectButton.hidden = true;
    _dfuButton.hidden = true;
    _textLabel.text = @"Connect to start";
    _connectButton.hidden = false;
    _lampLabel.hidden = true;
    _pirLabel.hidden = true;
    _ldrLabel.hidden = true;
    _tempLabel.hidden = true;
    _tempLabel2.hidden = true;
    _lampSwitch.hidden = true;
    _pirSwitch.hidden = true;
    _ldrBar.hidden = true;
    _setCurTimeButton.hidden = true;
    _setCusTimeButton.hidden = true;
    _colorUISlider.hidden = true;
    _colorScaleImage.hidden = true;
    _colorChosenImage.hidden = true;
    _imageBackground.hidden = true;
    _lampOffButton.hidden = true;
    _alphaImage.hidden = true;
    _alphaSlider.hidden = true;
    _setLampButton.hidden = true;
}

- (IBAction)enterDFU:(id)sender {
    
    // DFU button pressed: ask if sure
    
    UIAlertController *newAlert = [UIAlertController alertControllerWithTitle:@"Enter DFU mode" message:@"Are you sure you want to put the clock in DFU mode?" preferredStyle:UIAlertControllerStyleAlert];
    
    
    UIAlertAction *action = [UIAlertAction actionWithTitle:@"No" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        NSLog(@"No DFU");
        
    }];
    UIAlertAction *action2 = [UIAlertAction actionWithTitle:@"Yes" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        NSLog(@"Yes, enter DFU");
        
        // If sure to enter DFU mode, send the correct command via BT and hide UI
        
        NSData *dataToWrite = [NSData dataWithBytes:(uint8_t[]){0x00, 0x00, 0x00, 0x16, 0x00} length:5];
        [_myPeripheral writeValue:dataToWrite forCharacteristic:_colorCharacteristic
                             type:CBCharacteristicWriteWithResponse];
        NSLog(@"Entering DFU mode");
        [timer invalidate];
        _disconnectButton.hidden = true;
        _dfuButton.hidden = true;
        _textLabel.text = @"Connect to start";
        _connectButton.hidden = false;
        _lampLabel.hidden = true;
        _pirLabel.hidden = true;
        _ldrLabel.hidden = true;
        _tempLabel.hidden = true;
        _tempLabel2.hidden = true;
        _lampSwitch.hidden = true;
        _pirSwitch.hidden = true;
        _ldrBar.hidden = true;
        _setCurTimeButton.hidden = true;
        _setCusTimeButton.hidden = true;
        _colorUISlider.hidden = true;
        _colorScaleImage.hidden = true;
        _colorChosenImage.hidden = true;
        _imageBackground.hidden = true;
        _lampOffButton.hidden = true;
        _alphaImage.hidden = true;
        _alphaSlider.hidden = true;
        _setLampButton.hidden = true;
    }];
    
    [newAlert addAction:action];
    [newAlert addAction:action2];
    [self presentViewController:newAlert animated:true completion:nil];
    
}

- (IBAction)setCurTime:(id)sender {
    
    // Set current time button pressed: get time from device and send via BT
    
    NSDate *currentTime = [NSDate date]; // Get current time
    NSDateFormatter *outputFormatter = [[NSDateFormatter alloc] init];
    [outputFormatter setDateFormat:@"hh:mm:ss"];
    NSString *newDateString = [outputFormatter stringFromDate:currentTime]; // Put the time in a formatted string
    
    // Convert string into chars with each digit
    char hours1 = [newDateString characterAtIndex:0];
    char hours2 = [newDateString characterAtIndex:1];
    char mins1 = [newDateString characterAtIndex:3];
    char mins2 = [newDateString characterAtIndex:4];
    char sec1 = [newDateString characterAtIndex:6];
    char sec2 = [newDateString characterAtIndex:7];
    
    // Convert each digit into numbers in an array
    uint8_t timeToSet[3];
    timeToSet[0] = (hours1-48)*10 + hours2-48;
    timeToSet[1] = (mins1-48)*10 + mins2-48;
    timeToSet[2] = (sec1-48)*10 + sec2-48;
    NSLog(@"Time is: %d:%d:%d", timeToSet[0], timeToSet[1], timeToSet[2]);
    
    //[outputFormatter release];
    
    // Finally send this array
    NSData *dataToWrite = [NSData dataWithBytes:timeToSet length:3];
    [_myPeripheral writeValue:dataToWrite forCharacteristic:_timeCharacteristic
                         type:CBCharacteristicWriteWithResponse];
    NSLog(@"Current time is sent");
}

- (IBAction)setCusTime:(id)sender {
    
    // Set custom time button pressed: ask for the time and send it
    
    NSLog(@"Send custom time");
    UIAlertController *newAlert = [UIAlertController alertControllerWithTitle:@"Enter time to set" message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    [newAlert addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        {
            textField.placeholder=@"hh:mm:ss";
            textField.clearButtonMode=UITextFieldViewModeWhileEditing;
        }
    }];
    UIAlertAction *action = [UIAlertAction actionWithTitle:@"Set time" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        NSLog(@"Set time pressed");
        NSString *enteredTime = newAlert.textFields[0].text;
        
        // Convert string into chars with each digit
        char hours1 = [enteredTime characterAtIndex:0];
        char hours2 = [enteredTime characterAtIndex:1];
        char mins1 = [enteredTime characterAtIndex:3];
        char mins2 = [enteredTime characterAtIndex:4];
        char sec1 = [enteredTime characterAtIndex:6];
        char sec2 = [enteredTime characterAtIndex:7];
        
        // Convert each digit into numbers in an array
        uint8_t timeToSet[3];
        timeToSet[0] = (hours1-48)*10 + hours2-48;
        timeToSet[1] = (mins1-48)*10 + mins2-48;
        timeToSet[2] = (sec1-48)*10 + sec2-48;
        
        // Finally send this array
        NSData *dataToWrite = [NSData dataWithBytes:timeToSet length:3];
        [_myPeripheral writeValue:dataToWrite forCharacteristic:_timeCharacteristic
                             type:CBCharacteristicWriteWithResponse];
        
        NSLog(@"%d:%d:%d is sent", timeToSet[0], timeToSet[1], timeToSet[2]);
        
    }];
    UIAlertAction *action2 = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        NSLog(@"Cancel pressed");
    }];
    [newAlert addAction:action2];
    [newAlert addAction:action];
    [self presentViewController:newAlert animated:true completion:nil];
    
}

- (IBAction)colorSlider:(id)sender {
    
    float val = _colorUISlider.value;       // Get slider value
    int chosenInt = (int)(val*(float)1530); // Convert it to 6 pieces of 255
    
    // Convert the slider value to RGB colors, according to the picture
    // Red
    redInt = 0;
    if(chosenInt > 510) redInt = chosenInt - 510;
    // Green
    greenInt = 0;
    if(chosenInt < 765) greenInt = chosenInt;
    else if(chosenInt >= 765 && chosenInt < 1020) greenInt = 1020 - chosenInt;
    else if(chosenInt >= 1275) greenInt = chosenInt - 1275;
    // Blue
    blueInt = 255;
    if(chosenInt <= 510) blueInt = 510 - chosenInt;
    else if(chosenInt >= 1020) blueInt = chosenInt - 1020;
    else blueInt = 0;
    // Clip the values to 0-255 range
    if(redInt > 255) redInt = 255;
    else if(redInt < 0) redInt = 0;
    if(greenInt > 255) greenInt = 255;
    else if(greenInt < 0) greenInt = 0;
    if(blueInt > 255) blueInt = 255;
    else if(blueInt < 0) blueInt = 0;
    
    // Set the square to the chosen color
    UIColor *newColor = [UIColor colorWithRed:((float)redInt/256) green:((float)greenInt/255) blue:((float)blueInt/255) alpha:1];
    _colorChosenImage.backgroundColor = newColor;
}

- (IBAction)alphaChange:(id)sender {
    
}

- (IBAction)setLamp:(id)sender {
    
    // Get the color from sliders and send via BT
    
    uint8_t bytesToSend[5];
    bytesToSend[0] = (uint8_t)redInt*(_alphaSlider.value);
    bytesToSend[1] = (uint8_t)greenInt*(_alphaSlider.value);
    bytesToSend[2] = (uint8_t)blueInt*(_alphaSlider.value);
    bytesToSend[3] = 1;
    bytesToSend[4] = 255;
    
    NSLog(@"Setting lamp to R:G:B=%d:%d:%d", bytesToSend[0], bytesToSend[1], bytesToSend[2]);
    
    NSData *dataToWrite = [NSData dataWithBytes:bytesToSend length:5];
    [_myPeripheral writeValue:dataToWrite forCharacteristic:_colorCharacteristic
                         type:CBCharacteristicWriteWithResponse];
    
}

- (IBAction)lampOff:(id)sender {
    
    // Turn off the lamp by sending 0 as 4th byte
    
    NSData *dataToWrite = [NSData dataWithBytes:(uint8_t[]){0x00, 0x00, 0x00, 0x00, 0x00} length:5];
    [_myPeripheral writeValue:dataToWrite forCharacteristic:_colorCharacteristic
                         type:CBCharacteristicWriteWithResponse];
    NSLog(@"Lamp OFF");
    
}

- (void)peripheral:(CBPeripheral *)peripheral
didWriteValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    
    if(error){
        NSLog(@"Error writing characteristic value: %@", [error localizedDescription]);
    }
    
}

- (void)peripheral:(CBPeripheral *)peripheral
didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    
    // This is caused by the timer function, it reads the BT data and displays in UI
    
    NSData *data = characteristic.value;
    unsigned char *bytesList = [data bytes];
    
    if(bytesList[0]) _lampSwitch.on = true;
    else _lampSwitch.on = false;
    
    if(bytesList[1]) _pirSwitch.on = true;
    else _pirSwitch.on = false;
    
    _ldrBar.progress = (float)bytesList[2]/128;
    
    float temp = bytesList[3] + (float)bytesList[4]/256;
    _tempLabel2.text = [NSString stringWithFormat:@"%.2f°C", temp];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
