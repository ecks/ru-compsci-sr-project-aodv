import withinAreaPrototype as wap

print("1st check => calculateAngle(0,0, 1,0, 0,1): " + str(wap.calculateAngle(0.0,0.0,1.0,0.0,0.0,1.0)))

print("2st check => calculateAngle(0,0, 1,0, 2,0): " + str(wap.calculateAngle(0.0,0.0,1.0,0.0,2.0,0.0)))

print("3st check => calculateAngle(0,0, -1,0, 2,0): " + str(wap.calculateAngle(0.0,0.0,-1.0,0.0,2.0,0.0)))

print("4st check => calculateAngle(0,0, 0,1, 0,2): " + str(wap.calculateAngle(0.0,0.0,0.0,1.0,0.0,2.0)))

print("5st check => calculateAngle(0,0, 0,1, 0,-2): " + str(wap.calculateAngle(0.0,0.0,0.0,1.0,0.0,-2.0)))

print("6st check => calculateAngle(0,0, 1,1, 1,-1): " + str(wap.calculateAngle(0.0,0.0,1.0,1.0,1.0,-1.0)))

print("7st check => calculateAngle(0,0, 1,0, 1,-1): " + str(wap.calculateAngle(0.0,0.0,1.0,0.0,1.0,-1.0)))

print("8st check => calculateAngle(0,0, 0,1, 1,-1): " + str(wap.calculateAngle(0.0,0.0,0.0,1.0,1.0,-1.0)))
