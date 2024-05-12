#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple destination TCP port blocker");

static struct nf_hook_ops *nfho = NULL;

static u_int tcp_port = 80;

module_param(tcp_port, uint, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(tcp_port, "Port to be blocked");

static u_int hfunc(
    void *priv, 
    struct sk_buff *skb, 
    const struct nf_hook_state *state)
{
    struct iphdr *iph;
    struct tcphdr *tcph;
       
    if (!skb)
    {
        return NF_ACCEPT;
    }

    iph = ip_hdr(skb);
    
    if(iph->protocol == IPPROTO_TCP)
    {
        tcph = tcp_hdr(skb);
        
        if (ntohs(tcph->dest) == tcp_port) 
        {
            pr_info("port_blocker: Packet with destination port %u in TCP header is blocked!", tcp_port);
            return NF_DROP;
        }
    
        return NF_ACCEPT;
    }
    
    return NF_ACCEPT;
}

static int __init port_blocker_init(void)
{
    nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
    
    nfho->hook = (nf_hookfn*)hfunc;
    nfho->hooknum = NF_INET_LOCAL_OUT;

    
    nfho->pf = PF_INET;
    nfho->priority = NF_IP_PRI_FIRST;
    
    nf_register_net_hook(&init_net, nfho);
    
    return 0;
}

static void __exit port_blocker_exit(void)
{
    nf_unregister_net_hook(&init_net, nfho);
    kfree(nfho);
}

module_init(port_blocker_init);

module_exit(port_blocker_exit);