//
//  HxIterator
//  HelloWorld
//
//  Source generated by Haxe Swift target
//



class HxIterator  {
	
	
	func next () -> AnyObject? {
		
		var obj :AnyObject?
		self.p += 1
		return obj
	}
	func hasNext () -> Bool? {
		
		return self.p < self.len
	}
	var len :Int?
	var arr :Array?
	var p :Int?
	func init () {
		
		self.p = 0
		super.init()
	}
}
