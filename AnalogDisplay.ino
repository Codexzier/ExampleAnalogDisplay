// ========================================================================================
// Description:       render the value on a analog display
// ========================================================================================

// ========================================================================================
// function variables

float mCircumference = 2.0 * 3.14;
float mRadius = 30.0;

// ========================================================================================
// render the analog display
// ----------------------------------------------------------------------------------------
// locationX    = location x start postion from left
// locationY    = location y start postion from top
// val          = value to show with the pointer and text.
// maxValue     = max value input / limit value to hsow on end.
// clearPointer = the pointer and text write with color black.
// complete     = if true, the ellipse is draw with.
void renderAnalogDisplay(int locationX, int locationY, float val, float maxValue, bool clearPointer, bool complete) {

  float diff = mRadius - (((float)mRadius / 100.0) * 80.0);       // distance from target location
  float locPointerX = locationX + diff;                         // add distance for location X of the pointer
  float locPointerY = locationY + diff;                         // add distance for location Y of the pointer
  float diffSize = mRadius - (mRadius / 100.0 * 20.0);            // size for pointer

  if (complete) {                                               // if true, is draw with ellipse
    renderAnalogDisplayElements(locationX, locationY,           // draw the static analog elements.
                                diffSize);
  }

  if(val > maxValue) {
    val = maxValue;
  }
  float scaledValue = val * 50.0 / maxValue;                    // target scale value for the valuePointer
  renderValuePointer(locPointerX, locPointerY,                  // render value to pointer on display
                     diffSize, scaledValue, clearPointer);

  drawValueToText(locPointerX, locPointerY,                     // write the value to text.
                  val, clearPointer);
}

// ========================================================================================
// render all parts of non changing elements of analog display
// ----------------------------------------------------------------------------------------
// locationX    = location x start postion from left
// locationY    = location y start postion from top
// radius       = radius size of half circle
// diffSize     = sorry for wording. that is the end size of valuePointer
void renderAnalogDisplayElements(int locationX, int locationY, float diffSize){
    SetStrokeColor(1);
    SetFillColor(1);
    mScreen.rect(locationX - 1, locationY - 2, 63, 47);
    SetFillColor(2);
    mScreen.rect(locationX - 3, locationY - 2, 67, 50);

    SetStrokeColor(4);
    SetFillColor(4);
    mScreen.circle(locationX + mRadius, locationY + mRadius, mRadius);
    SetStrokeColor(3);
    SetFillColor(3);
    mScreen.circle(locationX + mRadius, locationY + mRadius, mRadius - 2);
    SetStrokeColor(0);
    SetFillColor(0);
    mScreen.circle(locationX + mRadius, locationY + mRadius, mRadius - 4);
    SetFillColor(0);
    mScreen.rect(locationX - 3, locationY + mRadius + 2, 67, 50);

    mScreen.noFill();
    
    renderStepLinesPointer(locationX, locationY, diffSize, mRadius, false); 
    renderStepLinesPointer(locationX, locationY, diffSize, mRadius, true); 
    
    mScreen.noFill();

    SetStrokeColor(1);
    SetFillColor(1);
    mScreen.rect(locationX - 3, locationY + mRadius + 1, 67, 17);

    mScreen.noFill();

    SetStrokeColor(1);
    SetFillColor(0);
    mScreen.rect(locationX + 4, locationY + mRadius + 2, 52, 12);

    mScreen.noFill();

    SetStrokeColor(4);
    mScreen.rect(locationX + 5, locationY + mRadius + 2, 50, 12); 
}

// ========================================================================================
// render five line steps
// ----------------------------------------------------------------------------------------
// locationX    = location x start postion from left
// locationY    = location y start postion from top
// radiusIn     = inner circle of start line
// radiusOut    = out circle of end line
// b            = that used to fix start and end line position rendering. I know, it is a easy fix.
void renderStepLinesPointer(int locationX, int locationY, float radiusIn, float radiusOut, bool b) {
 
  float f = 0.0;                                               // TODO: fix the workeround
  if(b) {
    f = .01;
  }

  float section = mCircumference / 10.0;
  float dif = radiusOut - radiusIn;

  float sectionStart = section * 5;
  float sectionEnd =   section * 11;

   SetStrokeColor(4);
  for (float iSection = sectionStart; iSection < sectionEnd; iSection = iSection + section) {

    float xIn = radiusIn *  cos(iSection + f) + radiusIn;
    float yIn = radiusIn * sin(iSection + f) + radiusIn;
    float xOut = radiusOut *  cos(iSection + f) + radiusOut;
    float yOut = radiusOut * sin(iSection + f) + radiusOut;

    mScreen.line(locationX + xIn + dif, locationY + yIn + dif,
                 locationX + xOut , locationY + yOut);
  }
}

// ========================================================================================
// render the value pointer to show a analog state
// ----------------------------------------------------------------------------------------
// locationX    = location x start postion from left
// locationY    = location y start postion from top
// val          = must being a scaled value
// clearPointer = draw the line in black or the same color of the background
void renderValuePointer(int locationX, int locationY, float diffRadius, float val, bool clearPointer) {

  if (clearPointer) {
    SetStrokeColor(0);
  }
  else {
    SetStrokeColor(3);
  }
  
  float section = mCircumference / 100.0;
  float sectionStart = section * 5;
  float center = diffRadius / 2.0;

  val = val + 50.0; // add move relative start point

  float x = diffRadius * cos(section * val) + diffRadius;
  float y = diffRadius * sin(section * val) + diffRadius;

  mScreen.line(locationX + diffRadius, locationY + diffRadius,
               locationX + x , locationY + y );
}

// ========================================================================================
// convert the value to text and write under the analog display part.
// ----------------------------------------------------------------------------------------
// locationX    = location x start postion from left
// locationY    = location y start postion from top
// val          = value to write on screen
// clearText    = write the value text in black or the same color of the background
void drawValueToText(int locationX, int locationY, float val,  bool clearText) {
  if (clearText) {
    SetStrokeColor(0);
  }
  else {
    SetStrokeColor(4);
  }

  String strValue = String(val);
  char chrArr[6];
  strValue.toCharArray(chrArr, 6);
  mScreen.setTextSize(1);
  mScreen.text(chrArr, locationX + 10, locationY + 28);
}

// ========================================================================================
// set a color for stroke and border
// ----------------------------------------------------------------------------------------
// colorNumber =  0 - Black
//                1 - Gray
//                2 - dark gray
//                3 - green
//                4 - green light
void SetStrokeColor(int colorNumber){
  switch(colorNumber) {
    case(0): {
      mScreen.stroke(0, 0, 0); break;
    }
    case(1): {
      mScreen.stroke(40, 40, 45); break;
    }
    case(2): {
      mScreen.stroke(20, 20, 25); break;
    }
    case(3): {
      mScreen.stroke(35, 200, 140); break;
    }
    case(4): {
      mScreen.stroke(40, 255, 180); break;
    }
    default: { 
      mScreen.stroke(255, 50, 50); break; 
    }
  }
}

// ========================================================================================
// set a color to fill
// ----------------------------------------------------------------------------------------
// colorNumber =  0 - Black
//                1 - Gray
//                2 - dark gray
//                3 - green
//                4 - green light
void SetFillColor(int colorNumber){
  switch(colorNumber) {
    case(0): {
      mScreen.fill(0, 0, 0); break;
    }
    case(1): {
      mScreen.fill(40, 40, 45); break;
    }
    case(2): {
      mScreen.fill(20, 20, 25); break;
    }
    case(3): {
      mScreen.fill(25, 255, 20); break;
    }
    case(4): {
      mScreen.fill(40, 255, 180); break;
    }
    default: { 
      mScreen.fill(255, 50, 50); break; 
    }
  }
}
