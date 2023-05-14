Flow:

Cron roota uruchamia "/root/cardashian_check.sh" 
    w pierwszym uruchomieniu "/root/cardashian_check.sh" odpala "/usr/bin/cardashian_cold_start.sh", potem czyści "/usr/bin/cardashian_cold_start.sh"

"cardashian_check.sh" pobiera "/root/tasks.sh"
"cardashian_check.sh" odpala "/root/tasks.sh"

w "/root/tasks.sh" moze byc np odpalanie "cardashian_update.sh"