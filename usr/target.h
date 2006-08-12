#ifndef __TARGET_H__
#define __TARGET_H__

/* better if we can include the followings in kernel header files. */
#define	MSG_SIMPLE_TAG	0x20
#define	MSG_HEAD_TAG	0x21
#define	MSG_ORDERED_TAG	0x22

#define	MAX_NR_HOST		1024
#define	DEFAULT_NR_DEVICE	64
#define	MAX_NR_DEVICE		(1 << 20)

#define	HASH_ORDER	4
#define	hashfn(cid)	hash_long((cid), HASH_ORDER)

struct mgmt_req {
	uint64_t mid;
	int busy;
	int function;
};

struct cmd {
	struct list_head hlist;
	struct list_head qlist;
	struct list_head clist;
	uint32_t cid;
	uint64_t uaddr;
	uint32_t len;
	int mmapped;
	struct tgt_device *dev;
	unsigned long state;

	/* Kill the followings when we use shared memory instead of netlink. */
	int hostno;
	uint32_t data_len;
	uint8_t scb[16];
	uint8_t lun[8];
	int attribute;
	uint64_t tag;
	struct mgmt_req *mreq;
};

struct target {
	int tid;
	int lid;

	struct list_head tlist;

	uint64_t max_device;
	struct tgt_device **devt;
	struct list_head device_list;

	struct list_head cmd_hash_list[1 << HASH_ORDER];
	struct list_head cmd_list;
	struct tgt_cmd_queue cmd_queue;
};

enum {
	TGT_QUEUE_BLOCKED,
	TGT_QUEUE_DELETED,
};

enum {
	TGT_CMD_QUEUED,
	TGT_CMD_PROCESSED,
};

#define QUEUE_FNS(bit, name)						\
static inline void set_queue_##name(struct tgt_cmd_queue *q)		\
{									\
	(q)->state |= (1UL << TGT_QUEUE_##bit);				\
}									\
static inline void clear_queue_##name(struct tgt_cmd_queue *q)		\
{									\
	(q)->state &= ~(1UL << TGT_QUEUE_##bit);			\
}									\
static inline int queue_##name(const struct tgt_cmd_queue *q)		\
{									\
	return ((q)->state & (1UL << TGT_QUEUE_##bit));			\
}

static inline int queue_active(const struct tgt_cmd_queue *q)		\
{									\
	return ((q)->active_cmd);					\
}

QUEUE_FNS(BLOCKED, blocked)
QUEUE_FNS(DELETED, deleted)

#define CMD_FNS(bit, name)						\
static inline void set_cmd_##name(struct cmd *c)			\
{									\
	(c)->state |= (1UL << TGT_CMD_##bit);				\
}									\
static inline void clear_cmd_##name(struct cmd *c)			\
{									\
	(c)->state &= ~(1UL << TGT_CMD_##bit);				\
}									\
static inline int cmd_##name(const struct cmd *c)			\
{									\
	return ((c)->state & (1UL << TGT_CMD_##bit));			\
}

CMD_FNS(QUEUED, queued)
CMD_FNS(PROCESSED, processed)

#endif