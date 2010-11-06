import withinAreaPrototype as wap

print("---------------------- Testing calculation of the angle ---------------")
print("1st check => calculateAngleOptimized(0,0, 1,0, 0,1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,0.0,0.0,1.0)))

print("2st check => calculateAngleOptimized(0,0, 1,0, 2,0): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,0.0,2.0,0.0)))

print("3st check => calculateAngleOptimized(0,0, -1,0, 2,0): " + str(wap.calculateAngleOptimized(0.0,0.0,-1.0,0.0,2.0,0.0)))

print("4st check => calculateAngleOptimized(0,0, 0,1, 0,2): " + str(wap.calculateAngleOptimized(0.0,0.0,0.0,1.0,0.0,2.0)))

print("5st check => calculateAngleOptimized(0,0, 0,1, 0,-2): " + str(wap.calculateAngleOptimized(0.0,0.0,0.0,1.0,0.0,-2.0)))

print("6st check => calculateAngleOptimized(0,0, 1,1, 1,-1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,1.0,1.0,-1.0)))

print("7st check => calculateAngleOptimized(0,0, 1,0, 1,-1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,0.0,1.0,-1.0)))

print("8st check => calculateAngleOptimized(0,0, 0,1, 1,-1): " + str(wap.calculateAngleOptimized(0.0,0.0,0.0,1.0,1.0,-1.0)))

print("9st check => calculateAngleOptimized(0,0, 1,2 2,1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,2.0,2.0,1.0)))

print("10st check => calculateAngleOptimized(0,0, 1,2 -2,-1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,2.0,-2.0,-1.0)))

print("11st check => calculateAngleOptimized(0,0, 1,2 -2,1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,2.0,-2.0,1.0)))

print("12st check => calculateAngleOptimized(1,1, 2,3 -1,2): " + str(wap.calculateAngleOptimized(1.0,1.0,2.0,3.0,-1.0,2.0)))

print("13st check => calculateAngleOptimized(0,0, 1,2, 1,-1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,2.0,1.0,-1.0)))

print("14st check => calculateAngleOptimized(0,0, 1,100 1,-100): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,100.0,1.0,-100.0)))

print("15st check => calculateAngleOptimized(0,0, 1,0, 1,1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,0.0,1.0,1.0)))

print("16st check => calculateAngleOptimized(0,0, 1,0, 1,-1): " + str(wap.calculateAngleOptimized(0.0,0.0,1.0,0.0,1.0,-1.0)))

print

print("---------------------------- Testing withinArea -----------------------")
print("1st check => withinArea(0,0, 1,0, 0,1, 0): " + str(wap.withinArea(0.0,0.0,1.0,0.0,0.0,1.0, 0)))

print("2st check => withinArea(0,0, 1,0, 2,0, 0): " + str(wap.withinArea(0.0,0.0,1.0,0.0,2.0,0.0, 0)))

print("3st check => withinArea(0,0, -1,0, 2,0, 0): " + str(wap.withinArea(0.0,0.0,-1.0,0.0,2.0,0.0, 0)))

print("4st check => withinArea(0,0, 0,1, 0,2, 0): " + str(wap.withinArea(0.0,0.0,0.0,1.0,0.0,2.0, 0)))

print("5st check => withinArea(0,0, 0,1, 0,-2, 0): " + str(wap.withinArea(0.0,0.0,0.0,1.0,0.0,-2.0, 0)))

print("6st check => withinArea(0,0, 1,1, 1,-1, 0): " + str(wap.withinArea(0.0,0.0,1.0,1.0,1.0,-1.0, 0)))

print("7st check => withinArea(0,0, 1,0, 1,-1, 0): " + str(wap.withinArea(0.0,0.0,1.0,0.0,1.0,-1.0, 0)))

print("8st check => withinArea(0,0, 0,1, 1,-1, 0): " + str(wap.withinArea(0.0,0.0,0.0,1.0,1.0,-1.0, 0)))

print("9st check => withinArea(0,0, 1,2 2,1, 0): " + str(wap.withinArea(0.0,0.0,1.0,2.0,2.0,1.0, 0)))

print("10st check => withinArea(0,0, 1,2 -2,-1, 0): " + str(wap.withinArea(0.0,0.0,1.0,2.0,-2.0,-1.0, 0)))

print("11st check => withinArea(0,0, 1,2 -2,1, 0): " + str(wap.withinArea(0.0,0.0,1.0,2.0,-2.0,1.0, 0)))

print("12st check => withinArea(1,1, 2,3 -1,2, 0): " + str(wap.withinArea(1.0,1.0,2.0,3.0,-1.0,2.0, 0)))

print("13st check => withinArea(0,0, 1,2, 1,-1, 0): " + str(wap.withinArea(0.0,0.0,1.0,2.0,1.0,-1.0, 0)))

print("14st check => withinArea(0,0, 1,100 1,-100, 0): " + str(wap.withinArea(0.0,0.0,1.0,100.0,1.0,-100.0, 0)))

print("15st check => withinArea(0,0, 1,0, 1,1, 0): " + str(wap.withinArea(0.0,0.0,1.0,0.0,1.0,1.0, 0)))

print("16st check => withinArea(0,0, 1,0, 1,-1, 0): " + str(wap.withinArea(0.0,0.0,1.0,0.0,1.0,-1.0, 0)))

print
