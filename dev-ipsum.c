/*
** dev-ipsum.c for Dev-Ipsum in /home/rohja/Projects/dev-ipsum
**
** Made by Paul "Rohja" Lesellier
** Login   <rohja@rohja.com>
**
** Started on  Thu Jan 10 19:16:41 2013 paul lesellier
*/

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Paul 'Rohja' Lesellier <rohja@rohja.com> wrote this file. As long as you
 * retain this notice you can do whatever you want with this stuff. If we meet
 * some day, and you think this stuff is worth it, you can buy me a beer
 * in return.
 * ----------------------------------------------------------------------------
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

/* License and Infos */
MODULE_LICENSE("BEER_WARE");
MODULE_DESCRIPTION("Lorem Ipsum Generator");
MODULE_AUTHOR("Paul 'Rohja' Lesellier <rohja@rohja.com>");

/* Prototypes and configuration */

/* Open*/
static int ipsum_open(struct inode *, struct file *);
/* Release */
static int ipsum_rls(struct inode *, struct file *);
/* Read */
static ssize_t ipsum_read(struct file *, char *, size_t, loff_t *);
/* Write */
static ssize_t ipsum_write(struct file *, const char *, size_t, loff_t *);
/* IOCTL */
static long ipsum_ioctl(struct file *, unsigned int, unsigned long);
/* Configuration */
static struct file_operations fops = {
  .read = ipsum_read,
  .open = ipsum_open,
  .write = ipsum_write,
  .release = ipsum_rls,
  .unlocked_ioctl = ipsum_ioctl,
};

/* Vars */
static char* ipsum_text = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, At accusam aliquyam diam diam dolore dolores duo eirmod eos erat, et nonumy sed tempor et et invidunt justo labore Stet clita ea et gubergren, kasd magna no rebum. sanctus sea sed takimata ut vero voluptua. est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat. Consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";

/* Init */
int init_module(void)
{
  int t;

  printk(KERN_ALERT "IPSUM LOADED\n");
  t = register_chrdev(89, "ipsum", &fops);
  if (t < 0)
    printk(KERN_ALERT "Device registration failed!...");
  else
    printk(KERN_ALERT "Device registred!");
  return t;
}

/* Exit */
void cleanup_module(void)
{
  printk(KERN_ALERT "IPSUM UNLOADED\n");
  unregister_chrdev(89, "ipsum");
}

/* Open*/
static int ipsum_open(struct inode *inode_, struct file *file_)
{
  printk(KERN_ALERT "Ipsum opened.");
  return 0;
}

/* Release */
static int ipsum_rls(struct inode *inode_, struct file *file_)
{
  printk(KERN_ALERT "Ipsum closed.");
  return 0;
}

/* Read */
static ssize_t ipsum_read(struct file *file_, char *output_buffer, size_t output_size, loff_t *off_)
{
  unsigned int i = 0;
  unsigned int ipsum_len;
  unsigned int count = 0;

  printk(KERN_ALERT "Trying to read %d Bytes from Ipsum.", (int)output_size);

  ipsum_len = strlen(ipsum_text);
  while (output_size)
    {
      put_user(ipsum_text[i++], output_buffer++);
      output_size--;
      if (i == ipsum_len)
	i = 0;
      count++;
    }
  return count;
}

/* Write */
static ssize_t ipsum_write(struct file *file_, const char *input_buffer, size_t input_size, loff_t *off_)
{
  printk(KERN_ALERT "Trying to write %d Bytes to Ipsum.", (int)input_size);
  return 0;
}

/* IOCTL */
static long ipsum_ioctl(struct file *file_, unsigned int ioctl_num, unsigned long ioctl_param)
{
  /*DEBUG*/
  printk("Ipsum IOCTL: num = %u, param = %u", ioctl_num, (long)ioctl_param);
  return 0;
}
