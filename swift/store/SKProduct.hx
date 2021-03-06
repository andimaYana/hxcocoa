package swift.store;

import swift.foundation.NSObject;
import swift.foundation.NSLocale;

@:framework("StoreKit")
extern class SKProduct extends NSObject {

	public var localizedDescription :String;
	public var localizedTitle :String;
	public var price :Float;
	public var priceLocale :NSLocale;
	public var productIdentifier :String;
	public var downloadable :Bool;
	public var downloadContentLengths :Array<Int>;
	public var downloadContentVersion :String;

}
