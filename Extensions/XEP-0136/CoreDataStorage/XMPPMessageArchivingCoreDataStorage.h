#import <Foundation/Foundation.h>

#import "XMPPCoreDataStorage.h"
#import "XMPPMessageArchiving.h"
#import "XMPPMessageArchiving_Message_CoreDataObject.h"
#import "XMPPMessageArchiving_Contact_CoreDataObject.h"

//Ashish


@interface XMPPMessageArchivingCoreDataStorage : XMPPCoreDataStorage <XMPPMessageArchivingStorage>
{
	/* Inherited protected variables from XMPPCoreDataStorage
	
	NSString *databaseFileName;
	NSUInteger saveThreshold;
	
	dispatch_queue_t storageQueue;
	 
	*/
}

/**
 * Convenience method to get an instance with the default database name.
 * 
 * IMPORTANT:
 * You are NOT required to use the sharedInstance.
 * 
 * If your application uses multiple xmppStreams, and you use a sharedInstance of this class,
 * then all of your streams share the same database store. You might get better performance if you create
 * multiple instances of this class instead (using different database filenames), as this way you can have
 * concurrent writes to multiple databases.
**/
+ (instancetype)sharedInstance;


@property (strong) NSString *messageEntityName;
@property (strong) NSString *contactEntityName;

/**
 * Defines elements within an archived message that will be tested for content presence
 * when determining whether to store the message. By default, only the body element is examined.
 */
@property (copy, nonatomic) NSArray<NSString *> *relevantContentXPaths;

- (NSEntityDescription *)messageEntity:(NSManagedObjectContext *)moc;
- (NSEntityDescription *)contactEntity:(NSManagedObjectContext *)moc;

- (XMPPMessageArchiving_Contact_CoreDataObject *)contactForMessage:(XMPPMessageArchiving_Message_CoreDataObject *)msg;

- (XMPPMessageArchiving_Contact_CoreDataObject *)contactWithJid:(XMPPJID *)contactJid
                                                      streamJid:(XMPPJID *)streamJid
                                           managedObjectContext:(NSManagedObjectContext *)moc;

- (XMPPMessageArchiving_Contact_CoreDataObject *)contactWithBareJidStr:(NSString *)contactBareJidStr streamBareJidStr:(NSString *)streamBareJidStr managedObjectContext:(NSManagedObjectContext *)moc;

- (XMPPMessageArchiving_Message_CoreDataObject *)composingMessageWithJid:(XMPPJID *)messageJid
                                                               streamJid:(XMPPJID *)streamJid
                                                                outgoing:(BOOL)isOutgoing
                                                    managedObjectContext:(NSManagedObjectContext *)moc;

- (void)willInsertMessage:(XMPPMessageArchiving_Message_CoreDataObject *)message;
- (void)didUpdateMessage:(XMPPMessageArchiving_Message_CoreDataObject *)message;
- (void)willDeleteMessage:(XMPPMessageArchiving_Message_CoreDataObject *)message;

- (void)willInsertContact:(XMPPMessageArchiving_Contact_CoreDataObject *)contact;
- (void)didUpdateContact:(XMPPMessageArchiving_Contact_CoreDataObject *)contact;

- (void)UpdateRecentMessageOfContactWithBareJidStr:(NSString *)contactBareJidStr managedObjectContext:(NSManagedObjectContext *)moc;

- (void)willInsertContact:(XMPPMessageArchiving_Contact_CoreDataObject *)contact;
- (void)didUpdateContact:(XMPPMessageArchiving_Contact_CoreDataObject *)contact;

- (void)insertUpdateNewContact:(XMPPMessage *)message outgoing:(BOOL)isOutgoing xmppStream:(XMPPStream *)xmppStream;
- (void)updateMessageStatus:(NSString *)messageId status:(NSString*)status;
- (void)updateDeletedMessage:(NSString *)messageId message_delete:(NSString*)message_delete;
- (void)updateMediaMessage:(NSString*)mediaUrl messageId:(NSString*)messageId;
- (void)setUnreadMessageToZero:(NSString*)bareJidStr;
- (void)deleteMessage:(NSString*)messageId;
- (void)clearAllMessage:(NSString*)bareJidStr isAllMessages:(BOOL)isAllMessages;
- (void)deleteAndExitChatRoom:(NSString*)bareJidStr isAllRooms:(BOOL)isAllRooms;

/* Inherited from XMPPCoreDataStorage
 * Please see the XMPPCoreDataStorage header file for extensive documentation.
 
- (id)initWithDatabaseFilename:(NSString *)databaseFileName storeOptions:(NSDictionary *)storeOptions;
- (id)initWithInMemoryStore;

@property (readonly) NSString *databaseFileName;
 
@property (readwrite) NSUInteger saveThreshold;

@property (readonly) NSManagedObjectModel *managedObjectModel;
@property (readonly) NSPersistentStoreCoordinator *persistentStoreCoordinator;

@property (readonly) NSManagedObjectContext *mainThreadManagedObjectContext;
 
*/

@end
