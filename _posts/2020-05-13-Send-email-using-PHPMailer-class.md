---
layout:         page
title:          "使用PHPMailer类发送电子邮件"
date:           2020-05-13 21:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
---

##### 一、下载phpMailer
[phpMailer](https://github.com/PHPMailer/PHPMailer) 是一个非常强大的PHP邮件发送类，可以设定发送邮件地址、回复地址、邮件主题、html网页、上传附件、并且使用起来非常方便。

以下测试使用 phpMailer 连接163邮箱服务，发送邮件。当然连接QQ邮箱服务发送邮件也一样的，唯一的区别是端口不一样，163的smtp服务使用25端口，而QQ的smtp服务使用587端口。

phpMailer包含以下5个类。此处要注意，把phpMailer的源码放到自己项目里的时候，要根据项目的文件结构，修改源码的命名空间，否则有可能出现调用不到的错误。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1ger493i2i2j30s108y0t3.jpg" alt="phpMailer源码" width="{{ page.width}}" align="bottom" />
<center>phpMailer源码</center>


##### 二、准备环境
PHPMailer通过socket连接邮件服务器，所以需要PHP环境需要装有sockets扩展，此外如果需要SSL加密邮件，还需要openssl扩展。

邮箱服务商默认是不允许用户在邮件客户端软件登陆的，但如果需要，需要去后台开启，并且获得授权码，使用邮箱地址+授权码在邮件客户端登陆。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1ger495elanj30kq0b53zq.jpg" alt="开启客户端登陆服务" width="{{ page.width}}" align="bottom" />
<center>开启客户端登陆服务</center>


##### 三、编写代码
一切准备好了，可以测试发邮件了：
```php
    public function sendEmail()
    {
        $mail = new \Task\Sdk\PHPMailer\PHPMailer(true);
        try {
            //发送邮件配置信息
            $email_setting = array(
                'host'=>"smtp.163.com",                     //smtp收件箱地址
                'port'=>"25",                               //smtp收件箱端口
                'username'=>"username1@163.com",            //smtp认真用户名和密码
                'password'=>"QTWIF*****STQC",               //登陆授权码
                'charset'=>"utf-8",                         //邮件字符编码
                'from'=>["username1@163.com", "username1"], //发件人地址
                'to'=>[                                     //收件人地址和名称，可多个
                    ["username2@163.com","username2"]
                ],
                'cc'=>[                                     //抄送地址和名称，可多个
                    ["username3@163.com","username3"]
                ],
                'bcc'=>[                                    //密抄送地址和名称，可多个
                    ["username4@qq.com","username4"]
                ],
            );

            
            $mail->isSMTP();                                //发送邮件，使用smtp协议               
            $mail->Host         = $email_setting['host'];                        
            $mail->SMTPAutoTLS  = false;                    //关闭自动启用TLS加密
            $mail->SMTPAuth     = true;                              
            $mail->Username     = $email_setting['username'];                 
            $mail->Password     = $email_setting['password'];                         
            $mail->Port         = $email_setting['port'];                                 
            $mail->CharSet      = $email_setting['charset'];                          

            //发件人
            $mail->setFrom($email_setting['from'][0], $email_setting['from'][1]);
            //收件人
            foreach($email_setting['to'] as $to){
                $mail->addAddress($to[0],$to[1]);
            }
            //抄送
            foreach($email_setting['cc'] as $cc){
                $mail->addCC($cc[0],$cc[1]);
            }
            //密抄送
            foreach($email_setting['bcc'] as $bcc){
                $mail->addBCC($bcc[0],$bcc[1]);
            }

            // Content
            $mail->isHTML(true);                            //email格式为HTML
            $mail->Subject = '这是一封测试邮件，不用理会';
            $mail->Body    = 'This is the HTML message body <b>in bold!</b>';

            $mail->send();
            echo 'Message has been sent';
        } catch (Exception $e) {
            echo "Message could not be sent. Mailer Error: {$mail->ErrorInfo}";
        }
    }
```

##### 四、补充
电子邮件中的CC 英文全称是 Carbon Copy(抄送)。

电子邮件中的BCC英文全称是 Blind Carbon Copy(暗抄送)。

两者的区别在于在BCC栏中的收件人可以看到所有的收件人名(TO，CC，BCC)，而在TO和CC栏中的收件人看不到BBC的收件人名。
