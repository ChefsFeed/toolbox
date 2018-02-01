//
//  UUHttpSession.h
//  Useful Utilities - Lightweight Objective C HTTP Client
//
//    License:
//  You are free to use this code for whatever purposes you desire. The only requirement is that you smile everytime you use it.
//
//  Contact: @cheesemaker or jon@threejacks.com
//
//  UUHttpSession provides a simple
//

#import <Foundation/Foundation.h>
#import "UUHttpResponseHandler.h"

@class  UUHttpResponse;

typedef void (^UUHttpSessionResponseHandler)(UUHttpResponse* response);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Construct a UUHttpRequest to pass to UUHttpSession
@interface UUHttpRequest : NSObject

- (id) initWithUrl:(NSString*)url;

@property (atomic, strong) NSString*        url;
@property (atomic, assign) UUHttpMethod        httpMethod;
@property (atomic, strong) NSDictionary*    queryArguments;
@property (atomic, strong) NSDictionary*    headerFields;
@property (atomic, strong) NSData*            body;
@property (atomic, assign) NSTimeInterval    timeout;
@property (atomic, strong) NSURLCredential* credentials;
@property (atomic, assign) BOOL                processMimeTypes;

@property (atomic, strong, readonly) NSURLRequest*    httpRequest;

// Static helper functions for the most common cases
+ (instancetype) getRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments;
+ (instancetype) deleteRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments;
+ (instancetype) putRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments body:(NSData*)body contentType:(NSString*)contentType;
+ (instancetype) postRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments body:(NSData*)body contentType:(NSString*)contentType;

//Basic auth helper functions
+ (instancetype) getRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments user:(NSString*)user password:(NSString*)password;
+ (instancetype) deleteRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments user:(NSString*)user password:(NSString*)password;
+ (instancetype) putRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments body:(NSData*)body contentType:(NSString*)contentType user:(NSString*)user password:(NSString*)password;
+ (instancetype) postRequest:(NSString*)url queryArguments:(NSDictionary*)queryArguments body:(NSData*)body contentType:(NSString*)contentType user:(NSString*)user password:(NSString*)password;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UUHttpResponse encapsulates the relevant info for an app to query after a UUHttpRequest has completed
@interface UUHttpResponse : NSObject

@property (atomic, strong) NSError*                httpError;
@property (atomic, strong) NSURLRequest*        httpRequest;
@property (atomic, strong) NSHTTPURLResponse*    httpResponse;
@property (atomic, strong) id                    parsedResponse;
@property (atomic, strong) NSData*                rawResponse;
@property (atomic, strong) NSString*            rawResponsePath;

- (NSString *)description;
- (NSString *)debugDescription;

@end


@interface UUHttpSession : NSObject

+ (void) setRequestTimeout:(NSTimeInterval)requestTimeout;

+ (UUHttpRequest*) executeRequest:(UUHttpRequest*)request completionHandler:(UUHttpSessionResponseHandler)completionHandler;

+ (UUHttpRequest*) get:(NSString*)url queryArguments:(NSDictionary*)queryArguments completionHandler:(UUHttpSessionResponseHandler)completionHandler;
+ (UUHttpRequest*) delete:(NSString*)url queryArguments:(NSDictionary*)queryArguments completionHandler:(UUHttpSessionResponseHandler)completionHandler;
+ (UUHttpRequest*) put:(NSString*)url queryArguments:(NSDictionary*)queryArguments putBody:(NSData*)putBody contentType:(NSString*)contentType completionHandler:(UUHttpSessionResponseHandler)completionHandler;
+ (UUHttpRequest*) post:(NSString*)url queryArguments:(NSDictionary*)queryArguments postBody:(NSData*)postBody contentType:(NSString*)contentType completionHandler:(UUHttpSessionResponseHandler)completionHandler;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Error constants

extern NSString * const kUUHttpSessionAppResponseKey;


