/*=============================================================================┐
|             _  _  _       _                                                  |  
|            (_)(_)(_)     | |                            _                    |██
|             _  _  _ _____| | ____ ___  ____  _____    _| |_ ___              |██
|            | || || | ___ | |/ ___) _ \|    \| ___ |  (_   _) _ \             |██
|            | || || | ____| ( (__| |_| | | | | ____|    | || |_| |            |██
|             \_____/|_____)\_)____)___/|_|_|_|_____)     \__)___/             |██
|                                                                              |██
|               ______                         _  _  _ _ _     _ _             |██
|              / _____)                       (_)(_)(_|_) |   (_) |            |██
|             ( (____  _   _  ____ _____  ____ _  _  _ _| |  _ _| |            |██
|              \____ \| | | |/ _  (____ |/ ___) || || | | |_/ ) |_|            |██
|              _____) ) |_| ( (_| / ___ | |   | || || | |  _ (| |_             |██
|             (______/|____/ \___ \_____|_|    \_____/|_|_| \_)_|_|            |██
|                           (_____|                                            |██
|                                                                              |██
|                         Copyright (c) 2015 Tong Kuo                          |██
|                                                                              |██
|                             ALL RIGHTS RESERVED.                             |██
|                                                                              |██
└==============================================================================┘██
  ████████████████████████████████████████████████████████████████████████████████
  ██████████████████████████████████████████████████████████████████████████████*/

@import Foundation;

#import "WikiConstants.h"

@class WikiHTTPSessionManager;
@class WikiSessionTask;
@class WikiPage;
@class WikiImage;
@class WikiSearchResult;

typedef NS_ENUM( NSUInteger, WikiEngineSearchApproach )
    { WikiEngineSearchApproachPageTitles    = 0
    , WikiEngineSearchApproachPageText      = 1
    , WikiEngineSearchApproachNearMatch     = 2
    };

typedef NSArray <__kindof WikiSearchResult*> WikiSearchResults;

// WikiEngine class
@interface WikiEngine : NSObject
    {
@protected
    NSURL                   __strong* _endpoint;
    WikiHTTPSessionManager  __strong* _wikiHTTPSessionManager;
    NSMutableArray          __strong* _tmpSessionTasksPool;

    NSString __strong* _ISOLanguageCode;
    }

@property ( strong, readonly ) NSURL* endpoint;
@property ( strong, readonly ) WikiHTTPSessionManager* wikiHTTPSessionManager;
@property ( strong, readonly ) NSString* ISOLanguageCode;

#pragma mark Creating Engine
// TODO: Init with a bulk of language codes
+ ( instancetype ) engineWithISOLanguageCode: ( NSString* )_ISOLanguageCode;
- ( instancetype ) initWithISOLanguageCode: ( NSString* )_ISOLanguageCode;

+ ( instancetype ) commonsEngine;

#pragma mark Controlling Query Task
@property ( assign, readonly ) BOOL hasCompletedAllQueryTasks;
@property ( assign, readonly ) NSUInteger numberOfRunningQueryTasks;
- ( void ) cancelAll;

#pragma mark Generic Methods to GET and POST
- ( WikiSessionTask* ) fetchResourceWithParameters: ( NSDictionary* )_Params
                                        HTTPMethod: ( NSString* )_HTTPMethod
                                           success: ( void (^)( NSURLSessionDataTask* _Task, id _ResponseObject ) )_SuccessBlock
                                           failure: ( void (^)( NSURLSessionDataTask* _Task, NSError* _Error ) )_FailureBlock
                                 stopAllOtherTasks: ( BOOL )_WillStop;

// Convenience
- ( WikiSessionTask* ) fetchResourceWithParameters: ( NSDictionary* )_Params
                                        HTTPMethod: ( NSString* )_HTTPMethod
                                           success: ( void (^)( NSURLSessionDataTask* _Task, id _ResponseObject ) )_SuccessBlock
                                           failure: ( void (^)( NSURLSessionDataTask* _Task, NSError* _Error ) )_FailureBlock;

#pragma mark Generic Methods to Query
- ( WikiSessionTask* ) queryList: ( NSString* )_ListValue
                 otherParameters: ( NSDictionary* )_ParamsDict
                         success: ( void (^)( NSURLSessionDataTask* _Task, id _ResponseObject ) )_SuccessBlock
                         failure: ( void (^)( NSURLSessionDataTask* _Task, NSError* _Error ) )_FailureBlock
               stopAllOtherTasks: ( BOOL )_WillStop;

// Convenience
- ( WikiSessionTask* ) queryList: ( NSString* )_ListValue
                 otherParameters: ( NSDictionary* )_ParamsDict
                         success: ( void (^)( NSURLSessionDataTask* _Task, id _ResponseObject ) )_SuccessBlock
                         failure: ( void (^)( NSURLSessionDataTask* _Task, NSError* _Error ) )_FailureBlock;

#pragma mark Search API
- ( WikiSessionTask* ) searchAllPagesThatHaveValue: ( NSString* )_SearchValue
                                      inNamespaces: ( NSArray* )_Namespaces
                                          approach: ( WikiEngineSearchApproach )_SearchApproach
                                             limit: ( NSUInteger )_Limit
                                           success: ( void (^)( WikiSearchResults* _SearchResults ) )_SuccessBlock
                                           failure: ( void (^)( NSError* _Error ) )_FailureBlock
                                 stopAllOtherTasks: ( BOOL )_WillStop;

// Convenience
- ( WikiSessionTask* ) searchAllPagesThatHaveValue: ( NSString* )_SearchValue
                                      inNamespaces: ( NSArray* )_Namespaces
                                          approach: ( WikiEngineSearchApproach )_SearchApproach
                                             limit: ( NSUInteger )_Limit
                                           success: ( void (^)( WikiSearchResults* _SearchResults ) )_SuccessBlock
                                           failure: ( void (^)( NSError* _Error ) )_FailureBlock;
#pragma Images API
- ( WikiSessionTask* ) fetchImage: ( NSString* )_ImageName
                          success: ( void (^)( WikiImage* _Image ) )_SuccessBlock
                          failure: ( void (^)( NSError* _Error ) )_FailureBlock
                stopAllOtherTasks: ( BOOL )_WillStop;

// Convenience
- ( WikiSessionTask* ) fetchImage: ( NSString* )_ImageName
                          success: ( void (^)( WikiImage* _Image ) )_SuccessBlock
                          failure: ( void (^)( NSError* _Error ) )_FailureBlock;

@end // WikiEngine class

/*================================================================================┐
|                              The MIT License (MIT)                              |
|                                                                                 |
|                           Copyright (c) 2015 Tong Kuo                           |
|                                                                                 |
|  Permission is hereby granted, free of charge, to any person obtaining a copy   |
|  of this software and associated documentation files (the "Software"), to deal  |
|  in the Software without restriction, including without limitation the rights   |
|    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell    |
|      copies of the Software, and to permit persons to whom the Software is      |
|            furnished to do so, subject to the following conditions:             |
|                                                                                 |
| The above copyright notice and this permission notice shall be included in all  |
|                 copies or substantial portions of the Software.                 |
|                                                                                 |
|   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    |
|    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     |
|   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   |
|     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      |
|  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  |
|  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  |
|                                    SOFTWARE.                                    |
└================================================================================*/