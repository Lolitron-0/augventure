<template>
  <div class="form_for_email">
    <div class="block_for_textEmail">
      <p class="text_email">***************************mail.ru</p>
    </div>
    <div class="block_for_btns">
      <my-button class="btn_email">Make it the main one</my-button>
      <my-button class="btn_email">Delete</my-button>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";

export default {
  components: {MyButton}

}
</script>

<style scoped>
.form_for_email{
  width: 100%;
  height: 40px;
  background-color: #0d1117;
  border: 1px solid #858585;
  position: relative;
}
.block_for_textEmail{
  width: 40%;
  height: 40px;
  border-right: 1px solid #858585;
  display: flex;
  align-items: center;
  position: absolute;
  left: 0;
}
.text_email{
  color: #cfcfcf;
  padding-left: 10px;

}
.block_for_btns{
  position: absolute;
  width: 60%;
  height: 40px;
  //border-left: 1px solid red;
  display: flex;
  justify-content: center;
  right: 0;
  padding: 5px 15px;
  gap: 100px;
}

.btn_email{
  color: #cfcfcf;
  width: 200px;
  height: 25px;
  border: none;
  justify-content: center;
  align-items: center;
}
@media (max-width: 1300px) {
  .block_for_btns{
    gap: 60px;
  }
  .btn_email{
    width: 170px;
    font-size: 12px;
  }
}
@media (max-width: 1100px) {
  .block_for_btns{
    gap: 40px;
  }
  .btn_email{
    width: 120px;
    font-size: 12px;
  }
  .block_for_btns{
    width: 55%;
  }
  .block_for_textEmail{
    width: 45%;
    font-size: 14px;
  }
}
@media (max-width: 992px) {

  .block_for_btns{
    gap: 30px;
  }
  .btn_email{
    width: 170px;
    font-size: 12px;
  }
  .block_for_btns{
    width: 55%;
  }
  .block_for_textEmail{
    width: 45%;
    font-size: 14px;
  }
}
@media (max-width: 769px) {
  .block_for_btns{
    gap: 30px;
  }
  .btn_email{
    width: 130px;
    font-size: 12px;
  }
  .block_for_btns{
    width: 55%;
  }
  .block_for_textEmail{
    width: 45%;
    font-size: 14px;
  }
}
</style>