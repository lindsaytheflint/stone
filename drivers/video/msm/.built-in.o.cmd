cmd_drivers/video/msm/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/video/msm/built-in.o drivers/video/msm/msm_fb.o drivers/video/msm/mdp.o drivers/video/msm/mdp_debugfs.o drivers/video/msm/mdp4_util.o drivers/video/msm/mdp4_hsic.o drivers/video/msm/mdp4_overlay.o drivers/video/msm/mdp4_overlay_lcdc.o drivers/video/msm/mdp4_overlay_dsi_video.o drivers/video/msm/mdp4_overlay_dsi_cmd.o drivers/video/msm/mdp4_dtv.o drivers/video/msm/mdp4_overlay_dtv.o drivers/video/msm/mdp_dma.o drivers/video/msm/mdp_dma_s.o drivers/video/msm/mdp_vsync.o drivers/video/msm/mdp_cursor.o drivers/video/msm/mdp_dma_tv.o drivers/video/msm/msm_dss_io_8960.o drivers/video/msm/msm_mipi.o drivers/video/msm/mipi_novatek.o drivers/video/msm/msm_fb_panel.o drivers/video/msm/mipi_novatek_720P_pt.o drivers/video/msm/hdmi_msm.o drivers/video/msm/external_common.o drivers/video/msm/mhl8240/built-in.o drivers/video/msm/vidc/built-in.o ; scripts/mod/modpost drivers/video/msm/built-in.o