--[[
	场景服要用到的模板表请在这require
]]
require("template.tables.tb_creature_template")
require("template.tables.tb_creature_resource")
require("template.tables.tb_anger_limit")

require("template.tables.tb_dailymission")
require("template.tables.tb_dailymission_buy")
require("template.tables.tb_dailymission_reward")
require("template.tables.tb_drop_reward")
require("template.tables.tb_feishengzhilu")
require("template.tables.tb_gameobject_template")
require("template.tables.tb_game_set")
require("template.tables.tb_gonggao")
require("template.tables.tb_grade_up")
require("template.tables.tb_grade_up_1")
require("template.tables.tb_grade_up_2")
require("template.tables.tb_grade_up_3")
require("template.tables.tb_grade_up_4")
require("template.tables.tb_grade_up_5")
require("template.tables.tb_grade_up_set_4")
require("template.tables.tb_instance_base")
require("template.tables.tb_instance_pro")
require("template.tables.tb_item_template")
require("template.tables.tb_char_level")
require("template.tables.tb_char_skill")
require("template.tables.tb_liudaolunhui")
require("template.tables.tb_liudaolunhui_object")
require("template.tables.tb_map_info")
require("template.tables.tb_ore")
require("template.tables.tb_ore_appear")
require("template.tables.tb_pantaoyuan")
require("template.tables.tb_qiyu")
require("template.tables.tb_quest_zhixian_condition")
require("template.tables.tb_quest_zhixian_follow")
require("template.tables.tb_quest_zhixian_open")
require("template.tables.tb_reward_random")
require("template.tables.tb_skill_base")
require("template.tables.tb_skill_uplevel")
require("template.tables.tb_spell_template")
require("template.tables.tb_wujiang_auction")
require("template.tables.tb_wujiang_auction_dlg")
require("template.tables.tb_wujiang_auction_time")
require("template.tables.tb_wujiang_base")
require("template.tables.tb_yunyouxianren")
require("template.tables.tb_quest_loot_item")
require("template.tables.tb_quest_Point_Info")
require("template.tables.tb_quest_talk")
require("template.tables.tb_quest_template")
require("template.tables.tb_quest_wo_relation")
require("template.tables.tb_battle_mode")
require("template.tables.tb_battle_killed_drop")
require("template.tables.tb_map")
require("template.tables.tb_map_vip")
require("template.tables.tb_drop_packet")
require("template.tables.tb_instance_trial")

-- 野外BOSS
require("template.tables.tb_field_boss")
require("template.tables.tb_field_boss_time")

-- 世界BOSS
require("template.tables.tb_worldboss_base")
require("template.tables.tb_worldboss_roll")
require("template.tables.tb_worldboss_rank_reward")
require("template.tables.tb_worldboss_rank_level_reward")
require("template.tables.tb_worldboss_waitroom")
require("template.tables.tb_worldboss_time")
require("template.tables.tb_worldboss_buff")

require("template.tables.tb_instance_res")
require("template.tables.tb_instance_reward")

require("template.tables.tb_mount_illusion")

-- 地图采集物
require("template.tables.tb_map_gameobject")
require("template.tables.tb_map_gameobject_detail")

-- buff
require("template.tables.tb_buff_template")
require("template.tables.tb_buff_effect")
require("template.tables.tb_buff_kuafu3v3")
require("template.tables.tb_buff_xianfu")

-- 跨服
require("template.tables.tb_kuafu3v3_base")
require("template.tables.tb_kuafu_xianfu_base")
require("template.tables.tb_kuafu_xianfu_boss")
require("template.tables.tb_kuafu_xianfu_killed_drop")
require("template.tables.tb_kuafu_xianfu_condition")

require("template.tables.tb_kuafu_xianfu_tst_base")
require("template.tables.tb_kuafu_xianfu_tst_boss")
require("template.tables.tb_kuafu_xianfu_tst_killed_drop")
require("template.tables.tb_kuafu_xianfu_tst_dummy")

require("template.tables.tb_doujiantai_base")

require("template.tables.tb_xiulianchang_base")
require("template.tables.tb_xiulianchang_dummy")

require("template.tables.tb_map_jump_point")
require("template.tables.tb_map_jump_point_detail")

require("template.tables.tb_item_quality_color")

require("template.tables.tb_char_info")

require("template.tables.tb_item_illusion")

--家族Boss

require("template.tables.tb_faction_bossdefense_base")
require("template.tables.tb_faction_bossdefense_point")
require("template.tables.tb_faction_bossdefense_pool")

require("template.tables.tb_faction_tower_base")
require("template.tables.tb_faction_tower_floor")

-- 世界冒险
require("template.tables.tb_risk_base")
require("template.tables.tb_risk_data")

-- 全名boss
require("template.tables.tb_mass_boss_base")
require("template.tables.tb_mass_boss_info")
require("template.tables.tb_mass_boss_loot")

require("template.tables.tb_single_pvp_base")
require("template.tables.tb_single_pvp_grade")
require("template.tables.tb_single_pvp_robot")

require("template.tables.tb_group_instance_base")

require("template.tables.tb_script_base")

require("template.tables.tb_mail")
require("template.tables.tb_job_info")
require("template.tables.tb_doujiantai_combat_win")
require("template.tables.tb_creature_worldrisk")

--vip
require("template.tables.tb_vip_base")


--个人Boss
require("template.tables.tb_private_boss_base")
require("template.tables.tb_private_boss_info")
require("template.tables.tb_private_boss_buff")

--战斗_血瓶
require("template.tables.tb_restore_potion_base")

-- 冒险任务
require("template.tables.tb_quest_adventure_base")
require("template.tables.tb_adventure_death_drop")
require("template.tables.tb_escort_base")
require("template.tables.tb_adventure_robot_base")
require("template.tables.tb_realmbreak_dailyquest_base")

--闯关
require("template.tables.tb_instance_stage")
require("template.tables.tb_instance_stage_base")
require("template.tables.tb_instance_stage_auto")

require("template.tables.tb_group_exp")
require("template.tables.tb_creature_group_exp")
require("template.tables.tb_instance_group_exp")

--家族战
require("template.tables.tb_faction_match_base")
require("template.tables.tb_faction_match_winstrike")
require("template.tables.tb_faction_match_rank_reward")
require("template.tables.tb_faction_match_champion")
require("template.tables.tb_faction_match_phase")

require("template.tables.tb_buff_base")
require("template.tables.tb_battle_force")
require("template.tables.tb_fabaoskill")

require("template.tables.tb_mount_base")


for _, ctInfo in pairs(tb_creature_template) do
	local ps = string.split(ctInfo.spell, ',')
	local ss = {}
	for i = 1, #ps, 5 do
		table.insert(ss, {tonumber(ps[ i ]), tonumber(ps[i+1]), tonumber(ps[i+2]), tonumber(ps[i+3]), tonumber(ps[i+4])})
	end
	ctInfo.spell = ss
end