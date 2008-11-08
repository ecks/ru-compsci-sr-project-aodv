import math

def withinArea(src_x, src_y, curr_x, curr_y, dst_x, dst_y, request_level):
	angle = (request_level+1) * 45.0
	if(calculateAngleOptimized(src_x, src_y, curr_x, curr_y, dst_x, dst_y) <= angle):
		return True
	else:
		return False

def calculateAngle(src_x, src_y, curr_x, curr_y, dst_x, dst_y):
	aSDNumer = dst_y-src_y
	aSDDenom = dst_x-src_x

	aSCNumer = curr_y-src_y
	aSCDenom = curr_x-src_x
	if(aSDDenom == 0.0 and aSCDenom == 0.0):
		return 0.0
	elif(aSDDenom == 0.0 and aSCNumer == 0.0):
		return 90.0
	elif(aSDDenom == 0.0):
		aSC = aSCNumer/aSCDenom
		return math.degrees(math.atan(1/aSC))
	elif(aSCDenom == 0.0 and aSDNumer == 0.0):
		return 90.0
	elif(aSCDenom == 0.0):
	        aSD = aSDNumer/aSDDenom
		return math.degrees(math.atan(1/aSD))
	elif(aSDNumer == 0.0 and aSCNumer == 0.0):
		return 0.0
	elif(aSCNumer == 0.0):
		aSD = aSDNumer/aSDDenom
		return math.degrees(math.atan(aSD))
	elif(aSDNumer == 0.0):
		aSC = aSCNumer/aSCDenom
		return math.degrees(math.atan(aSC))
	else:
	  aSD = aSDNumer/aSDDenom
	  aSC = aSCNumer/aSCDenom
	  if(aSD*aSC == -1):
		return 90.0
	  else:
		return math.degrees(math.atan((aSC-aSD)/(1 + (aSC*aSD))))

def calculateAngleOptimized(src_x, src_y, curr_x, curr_y, dst_x, dst_y):
	aSDNumer = dst_y-src_y
	aSDDenom = dst_x-src_x

	aSCNumer = curr_y-src_y
	aSCDenom = curr_x-src_x

 	# arcos 
	#   (normalize ((aSDDenom,aSDNumer) dot-product (aSCDenom,aSCNumer)))
        
	sdLength = math.sqrt(math.pow(aSDDenom,2) + math.pow(aSDNumer,2))
	scLength = math.sqrt(math.pow(aSCDenom,2) + math.pow(aSCNumer,2))
	
	formNumer = (aSDDenom*aSCDenom) + (aSDNumer*aSCNumer)
	formDenom = sdLength * scLength

#	return (math.degrees(math.acos(math.fabs(formNumer/formDenom))))

	return (round(math.degrees(math.acos(formNumer/formDenom)), 5))

