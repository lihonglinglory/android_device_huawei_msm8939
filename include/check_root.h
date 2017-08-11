#ifndef _CHECK_ROOT_H_
#define _CHECK_ROOT_H_
/*< DTS2014120404357 yedapeng 20141201 begin*/
/*< DTS2014091203249 yangpanfei 20140915 begin*/
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>

#define CHECKROOT_SETUID_FLAG     (1 << 0)
#define CHECKROOT_SETGID_FLAG     (1 << 1)
#define CHECKROOT_SETRESUID_FLAG  (1 << 2)
#define CHECKROOT_SETRESGID_FLAG  (1 << 3)

struct checkroot_ref_cnt {
	int setuid;
	int setgid;
	int setresuid;
	int setresgid;
};

int checkroot_setuid(uid_t uid);
int checkroot_setgid(gid_t gid);
int checkroot_setresuid(uid_t uid);
int checkroot_setresgid(gid_t gid);

#endif
/*DTS2014091203249 yangpanfei 20140915 end >*/
/*DTS2014120404357 yedapeng 20141201 end >*/